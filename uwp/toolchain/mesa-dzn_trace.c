/* D3D12 command list call tracer for debugging Dozen on the Xbox (no D3D12 debug layer there).
 * dzn_trace_macros.h routes every ID3D12GraphicsCommandList*_X() macro call through dzn_trace_note(). */
#include <stdint.h>
#include "util/log.h"

void dzn_trace_note(const void *list, const char *method);
void dzn_trace_dump(const void *list, unsigned last);
static void dzn_trace_dump_copies(const void *list);

/* 4096 was too short: MK Komplete's failing list had more calls than that since its Reset. */
#define DZN_TRACE_RING 65536

struct dzn_trace_entry { const void *list; const char *method; };
static struct dzn_trace_entry dzn_trace_ring[DZN_TRACE_RING];
static uint32_t dzn_trace_pos;

void
dzn_trace_note(const void *list, const char *method)
{
   uint32_t i = __atomic_fetch_add(&dzn_trace_pos, 1, __ATOMIC_RELAXED) % DZN_TRACE_RING;
   dzn_trace_ring[i].list = list;
   dzn_trace_ring[i].method = method;
}

/* Print the last calls made on this command list (since its last Reset), oldest first. */
void
dzn_trace_dump(const void *list, unsigned last)
{
   uint32_t end = __atomic_load_n(&dzn_trace_pos, __ATOMIC_RELAXED);
   uint32_t begin = end > DZN_TRACE_RING ? end - DZN_TRACE_RING : 0;
   uint32_t start = begin;
   for (uint32_t i = end; i-- > begin;) {
      const struct dzn_trace_entry *e = &dzn_trace_ring[i % DZN_TRACE_RING];
      if (e->list == list && e->method && !__builtin_strcmp(e->method, "Reset")) {
         start = i;
         break;
      }
   }
   unsigned count = 0;
   for (uint32_t i = start; i != end; i++)
      count += dzn_trace_ring[i % DZN_TRACE_RING].list == list;
   mesa_loge("dzn: %u D3D12 calls on this command list since its Reset (trace seq %u, showing last %u):", count, start, last);
   unsigned skip = count > last ? count - last : 0, n = 0;
   for (uint32_t i = start; i != end; i++) {
      const struct dzn_trace_entry *e = &dzn_trace_ring[i % DZN_TRACE_RING];
      if (e->list != list || n++ < skip)
         continue;
      mesa_loge("dzn:   #%u %s", n - 1, e->method);
   }
   dzn_trace_dump_copies(list);
}

/* ---- Scratch-list probing ----------------------------------------------------------------
 * Each self-contained call is replayed on its own scratch command list, which is closed right
 * away: if Close() fails, that call alone is invalid on this device. Enabled by DZN_PROBE. */
#define COBJMACROS
#include <stdlib.h>
#include "c11/threads.h"
#include <directx/d3d12.h>
#include "dzn_trace_macros.h"

void *dzn_probe_list_ = NULL;
void *dzn_probe_begin(void *list);
int dzn_probe_end(const char *method);

static ID3D12CommandAllocator *probe_alloc;
static ID3D12GraphicsCommandList *probe_list;
static mtx_t probe_mtx;
static once_flag probe_once = ONCE_FLAG_INIT;
static int probe_enabled = -1;
static unsigned probe_count, probe_failures, probe_limit = 200000;

static void
probe_init_mtx(void)
{
   mtx_init(&probe_mtx, mtx_plain);
}

void *
dzn_probe_begin(void *list)
{
   if (probe_enabled < 0) {
      /* DZN_PROBE=<n> probes the first n calls, DZN_PROBE=0 all of them (a crash minutes into a game). */
      const char *env = getenv("DZN_PROBE");
      probe_enabled = env != NULL;
      if (env && *env >= '0' && *env <= '9')
         probe_limit = strtoul(env, NULL, 10);
   }
   if (!probe_enabled || probe_failures >= 32 || (probe_limit && probe_count >= probe_limit))
      return NULL;

   call_once(&probe_once, probe_init_mtx);
   mtx_lock(&probe_mtx);
   if (!probe_list) {
      ID3D12GraphicsCommandList *l = list;
      ID3D12Device *dev = NULL;
      if (FAILED(l->lpVtbl->GetDevice(l, &IID_ID3D12Device, (void **)&dev)) ||
          FAILED(dev->lpVtbl->CreateCommandAllocator(dev, D3D12_COMMAND_LIST_TYPE_DIRECT, &IID_ID3D12CommandAllocator, (void **)&probe_alloc)) ||
          FAILED(dev->lpVtbl->CreateCommandList(dev, 0, D3D12_COMMAND_LIST_TYPE_DIRECT, probe_alloc, NULL, &IID_ID3D12GraphicsCommandList, (void **)&probe_list))) {
         mesa_loge("dzn: probe: could not create scratch command list");
         probe_enabled = 0;
         mtx_unlock(&probe_mtx);
         return NULL;
      }
      dev->lpVtbl->Release(dev);
      mesa_logi("dzn: probe: replaying self-contained D3D12 calls on a scratch list");
   } else {
      probe_alloc->lpVtbl->Reset(probe_alloc);
      probe_list->lpVtbl->Reset(probe_list, probe_alloc, NULL);
   }
   probe_count++;
   return probe_list;
}

int
dzn_probe_end(const char *method)
{
   HRESULT hr = probe_list->lpVtbl->Close(probe_list);
   int failed = FAILED(hr);
   if (failed) {
      probe_failures++;
      mesa_loge("dzn: probe: %s alone breaks a command list (Close 0x%08x, probe #%u)", method, (unsigned)hr, probe_count);
   }
   mtx_unlock(&probe_mtx);
   return failed;
}

#define LOC_FMT "type %d res %p sub %u | fp off %llu fmt %d %ux%ux%u pitch %u"
#define LOC_ARGS(l) (int)(l)->Type, (void *)(l)->pResource, (l)->SubresourceIndex, \
   (unsigned long long)(l)->PlacedFootprint.Offset, (int)(l)->PlacedFootprint.Footprint.Format, \
   (l)->PlacedFootprint.Footprint.Width, (l)->PlacedFootprint.Footprint.Height, \
   (l)->PlacedFootprint.Footprint.Depth, (l)->PlacedFootprint.Footprint.RowPitch

void
dzn_probe_detail_ResourceBarrier(UINT n, const D3D12_RESOURCE_BARRIER *b)
{
   for (UINT i = 0; i < n; i++) {
      if (b[i].Type == D3D12_RESOURCE_BARRIER_TYPE_TRANSITION) {
         D3D12_RESOURCE_DESC d;
         b[i].Transition.pResource->lpVtbl->GetDesc(b[i].Transition.pResource, &d);
         mesa_loge("dzn:   [%u] transition flags 0x%x res %p (dim %d fmt %d %llux%u flags 0x%x) sub 0x%x: 0x%x -> 0x%x",
                   i, b[i].Flags, (void *)b[i].Transition.pResource, (int)d.Dimension, (int)d.Format,
                   (unsigned long long)d.Width, d.Height, d.Flags, b[i].Transition.Subresource,
                   b[i].Transition.StateBefore, b[i].Transition.StateAfter);
      } else {
         mesa_loge("dzn:   [%u] type %d flags 0x%x", i, (int)b[i].Type, b[i].Flags);
      }
   }
}

void
dzn_probe_detail_CopyTextureRegion(const D3D12_TEXTURE_COPY_LOCATION *dst, UINT x, UINT y, UINT z,
                                   const D3D12_TEXTURE_COPY_LOCATION *src, const D3D12_BOX *box)
{
   mesa_loge("dzn:   dst " LOC_FMT " at %u,%u,%u", LOC_ARGS(dst), x, y, z);
   mesa_loge("dzn:   src " LOC_FMT, LOC_ARGS(src));
   if (box)
      mesa_loge("dzn:   box %u,%u,%u - %u,%u,%u", box->left, box->top, box->front, box->right, box->bottom, box->back);
   for (int i = 0; i < 2; i++) {
      const D3D12_TEXTURE_COPY_LOCATION *l = i ? src : dst;
      D3D12_RESOURCE_DESC d;
      l->pResource->lpVtbl->GetDesc(l->pResource, &d);
      mesa_loge("dzn:   %s resource: dim %d fmt %d %llux%ux%u mips %u samples %u layout %d flags 0x%x",
                i ? "src" : "dst", (int)d.Dimension, (int)d.Format, (unsigned long long)d.Width, d.Height,
                d.DepthOrArraySize, d.MipLevels, d.SampleDesc.Count, (int)d.Layout, d.Flags);
   }
}

void
dzn_probe_detail_ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE rtv, const FLOAT *c, UINT n, const D3D12_RECT *r)
{
   mesa_loge("dzn:   rtv 0x%llx color %f %f %f %f rects %u%s", (unsigned long long)rtv.ptr, c[0], c[1], c[2], c[3], n, r ? "" : " (null)");
   for (UINT i = 0; r && i < n; i++)
      mesa_loge("dzn:   rect %ld,%ld - %ld,%ld", r[i].left, r[i].top, r[i].right, r[i].bottom);
}

void
dzn_probe_detail_OMSetRenderTargets(UINT n, const D3D12_CPU_DESCRIPTOR_HANDLE *rtvs, BOOL single, const D3D12_CPU_DESCRIPTOR_HANDLE *dsv)
{
   mesa_loge("dzn:   %u rtvs (single %d) first 0x%llx dsv %s0x%llx", n, single, rtvs ? (unsigned long long)rtvs[0].ptr : 0ull,
             dsv ? "" : "null ", dsv ? (unsigned long long)dsv->ptr : 0ull);
}

void
dzn_probe_detail_IASetVertexBuffers(UINT start, UINT n, const D3D12_VERTEX_BUFFER_VIEW *v)
{
   for (UINT i = 0; v && i < n; i++)
      mesa_loge("dzn:   vb %u: va 0x%llx size %u stride %u", start + i, (unsigned long long)v[i].BufferLocation, v[i].SizeInBytes, v[i].StrideInBytes);
}

void
dzn_probe_detail_RSSetViewports(UINT n, const D3D12_VIEWPORT *v)
{
   for (UINT i = 0; i < n; i++)
      mesa_loge("dzn:   vp %u: %f,%f %fx%f depth %f-%f", i, v[i].TopLeftX, v[i].TopLeftY, v[i].Width, v[i].Height, v[i].MinDepth, v[i].MaxDepth);
}

void
dzn_probe_detail_RSSetScissorRects(UINT n, const D3D12_RECT *r)
{
   for (UINT i = 0; i < n; i++)
      mesa_loge("dzn:   scissor %u: %ld,%ld - %ld,%ld", i, r[i].left, r[i].top, r[i].right, r[i].bottom);
}

/* ---- Last copies --------------------------------------------------------------------------
 * Always on (no DZN_PROBE needed): the arguments of the last copies are kept, and the ones on a
 * command list that fails to close are printed with their resources, since a copy is usually
 * among its last calls (L.A. Noire, the resolution-scale change). */
#define DZN_COPY_RING 256

struct dzn_trace_copy {
   const void *list;
   int buffer;
   D3D12_TEXTURE_COPY_LOCATION dst, src;
   UINT x, y, z;
   int has_box;
   D3D12_BOX box;
   UINT64 dst_off, src_off, size;
};
static struct dzn_trace_copy dzn_copy_ring[DZN_COPY_RING];
static uint32_t dzn_copy_pos;

/* Checks each copy as it is recorded against what D3D12 accepts, and logs the first invalid ones
 * with their trace sequence number (the dump of a failing list prints the seq of its Reset), so a
 * bad copy is found even when it is thousands of calls before Close. */
static unsigned dzn_copy_invalid;

static unsigned
dzn_trace_planes(DXGI_FORMAT f)
{
   switch (f) {
   case DXGI_FORMAT_D24_UNORM_S8_UINT: case DXGI_FORMAT_R24G8_TYPELESS:
   case DXGI_FORMAT_R24_UNORM_X8_TYPELESS: case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
   case DXGI_FORMAT_D32_FLOAT_S8X24_UINT: case DXGI_FORMAT_R32G8X24_TYPELESS:
   case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS: case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
   case DXGI_FORMAT_NV12: case DXGI_FORMAT_P010: case DXGI_FORMAT_P016:
      return 2;
   default:
      return 1;
   }
}

/* Size of the location's subresource (texture) or footprint; 0 and a reason when it is invalid. */
static int
dzn_trace_loc_size(const D3D12_TEXTURE_COPY_LOCATION *l, UINT *w, UINT *h, UINT *d, const char **why)
{
   D3D12_RESOURCE_DESC desc;
   l->pResource->lpVtbl->GetDesc(l->pResource, &desc);
   if (l->Type == D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT) {
      const D3D12_SUBRESOURCE_FOOTPRINT *f = &l->PlacedFootprint.Footprint;
      *w = f->Width; *h = f->Height; *d = f->Depth;
      if (desc.Dimension != D3D12_RESOURCE_DIMENSION_BUFFER) { *why = "footprint on a texture"; return 0; }
      if (l->PlacedFootprint.Offset % D3D12_TEXTURE_DATA_PLACEMENT_ALIGNMENT) { *why = "footprint offset not 512-aligned"; return 0; }
      if (f->RowPitch % D3D12_TEXTURE_DATA_PITCH_ALIGNMENT) { *why = "row pitch not 256-aligned"; return 0; }
      if (!f->Width || !f->Height || !f->Depth) { *why = "empty footprint"; return 0; }
      const int bc = (f->Format >= DXGI_FORMAT_BC1_TYPELESS && f->Format <= DXGI_FORMAT_BC5_SNORM) ||
                     (f->Format >= DXGI_FORMAT_BC6H_TYPELESS && f->Format <= DXGI_FORMAT_BC7_UNORM_SRGB);
      const UINT rows = bc ? (f->Height + 3) / 4 : f->Height;
      /* The last row only needs its used bytes, so count whole pitches up to the row before it. */
      if (l->PlacedFootprint.Offset + (UINT64)f->RowPitch * ((UINT64)rows * f->Depth - 1) > desc.Width) { *why = "footprint past the end of the buffer"; return 0; }
      return 1;
   }
   if (desc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER) { *why = "subresource index on a buffer"; return 0; }
   const UINT mips = desc.MipLevels ? desc.MipLevels : 1;
   const UINT layers = desc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE3D ? 1 : desc.DepthOrArraySize;
   if (l->SubresourceIndex >= mips * layers * dzn_trace_planes(desc.Format)) { *why = "subresource index out of range"; return 0; }
   const UINT mip = l->SubresourceIndex % mips;
   *w = (UINT)(desc.Width >> mip) ? (UINT)(desc.Width >> mip) : 1;
   *h = (desc.Height >> mip) ? (desc.Height >> mip) : 1;
   *d = desc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE3D ? ((desc.DepthOrArraySize >> mip) ? (desc.DepthOrArraySize >> mip) : 1) : 1;
   /* Block-compressed mips are copied in whole 4x4 blocks, even when the mip is smaller. */
   if ((desc.Format >= DXGI_FORMAT_BC1_TYPELESS && desc.Format <= DXGI_FORMAT_BC5_SNORM) ||
       (desc.Format >= DXGI_FORMAT_BC6H_TYPELESS && desc.Format <= DXGI_FORMAT_BC7_UNORM_SRGB)) {
      *w = (*w + 3) & ~3u;
      *h = (*h + 3) & ~3u;
   }
   return 1;
}

static void
dzn_trace_check_copy(const void *list, const D3D12_TEXTURE_COPY_LOCATION *dst, UINT x, UINT y, UINT z,
                     const D3D12_TEXTURE_COPY_LOCATION *src, const D3D12_BOX *box)
{
   UINT sw, sh, sd, dw, dh, dd;
   const char *why = NULL;
   if (!dzn_trace_loc_size(src, &sw, &sh, &sd, &why) || !dzn_trace_loc_size(dst, &dw, &dh, &dd, &why)) {
      /* why is set */
   } else if (box && (box->left >= box->right || box->top >= box->bottom || box->front >= box->back)) {
      why = "empty box";
   } else if (box && (box->right > sw || box->bottom > sh || box->back > sd)) {
      why = "box past the source";
   } else {
      const UINT cw = box ? box->right - box->left : sw, ch = box ? box->bottom - box->top : sh, cd = box ? box->back - box->front : sd;
      if ((UINT64)x + cw > dw || (UINT64)y + ch > dh || (UINT64)z + cd > dd)
         why = "copy past the destination";
   }
   if (!why)
      return;
   if (__atomic_fetch_add(&dzn_copy_invalid, 1, __ATOMIC_RELAXED) >= 64)
      return;
   mesa_loge("dzn: invalid CopyTextureRegion (%s) on list %p at trace seq %u:", why, list,
             __atomic_load_n(&dzn_trace_pos, __ATOMIC_RELAXED) - 1);
   dzn_probe_detail_CopyTextureRegion(dst, x, y, z, src, box);
}

/* Transition barriers name one subresource (or all of them); an index past mips x layers x planes,
 * such as a stencil plane on a color image, breaks the command list the same way a bad copy does. */
void
dzn_trace_check_barriers(const void *list, UINT n, const D3D12_RESOURCE_BARRIER *b)
{
   for (UINT i = 0; i < n; i++) {
      if (b[i].Type != D3D12_RESOURCE_BARRIER_TYPE_TRANSITION ||
          b[i].Transition.Subresource == D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES)
         continue;
      D3D12_RESOURCE_DESC d;
      b[i].Transition.pResource->lpVtbl->GetDesc(b[i].Transition.pResource, &d);
      const UINT count = d.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER ? 1 :
         (d.MipLevels ? d.MipLevels : 1) * (d.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE3D ? 1 : d.DepthOrArraySize) *
         dzn_trace_planes(d.Format);
      if (b[i].Transition.Subresource < count ||
          __atomic_fetch_add(&dzn_copy_invalid, 1, __ATOMIC_RELAXED) >= 64)
         continue;
      mesa_loge("dzn: invalid ResourceBarrier [%u] (subresource %u of %u) on list %p at trace seq %u:", i,
                b[i].Transition.Subresource, count, list, __atomic_load_n(&dzn_trace_pos, __ATOMIC_RELAXED) - 1);
      dzn_probe_detail_ResourceBarrier(1, &b[i]);
   }
}

void
dzn_trace_copy_tex(const void *list, const D3D12_TEXTURE_COPY_LOCATION *dst, UINT x, UINT y, UINT z,
                   const D3D12_TEXTURE_COPY_LOCATION *src, const D3D12_BOX *box)
{
   dzn_trace_check_copy(list, dst, x, y, z, src, box);
   struct dzn_trace_copy *c = &dzn_copy_ring[__atomic_fetch_add(&dzn_copy_pos, 1, __ATOMIC_RELAXED) % DZN_COPY_RING];
   c->list = NULL;
   c->buffer = 0;
   c->dst = *dst;
   c->src = *src;
   c->x = x; c->y = y; c->z = z;
   c->has_box = box != NULL;
   if (box)
      c->box = *box;
   __atomic_store_n(&c->list, list, __ATOMIC_RELEASE);
}

void
dzn_trace_copy_buf(const void *list, ID3D12Resource *dst, UINT64 dst_off, ID3D12Resource *src, UINT64 src_off, UINT64 size)
{
   D3D12_RESOURCE_DESC dd, sd;
   dst->lpVtbl->GetDesc(dst, &dd);
   src->lpVtbl->GetDesc(src, &sd);
   if ((dst_off + size > dd.Width || src_off + size > sd.Width || !size) &&
       __atomic_fetch_add(&dzn_copy_invalid, 1, __ATOMIC_RELAXED) < 64)
      mesa_loge("dzn: invalid CopyBufferRegion on list %p at trace seq %u: %llu bytes, dst %p+%llu of %llu, src %p+%llu of %llu",
                list, __atomic_load_n(&dzn_trace_pos, __ATOMIC_RELAXED) - 1, (unsigned long long)size,
                (void *)dst, (unsigned long long)dst_off, (unsigned long long)dd.Width,
                (void *)src, (unsigned long long)src_off, (unsigned long long)sd.Width);
   struct dzn_trace_copy *c = &dzn_copy_ring[__atomic_fetch_add(&dzn_copy_pos, 1, __ATOMIC_RELAXED) % DZN_COPY_RING];
   c->list = NULL;
   c->buffer = 1;
   c->dst.pResource = dst;
   c->src.pResource = src;
   c->dst_off = dst_off; c->src_off = src_off; c->size = size;
   __atomic_store_n(&c->list, list, __ATOMIC_RELEASE);
}

static void
dzn_trace_dump_copies(const void *list)
{
   uint32_t end = __atomic_load_n(&dzn_copy_pos, __ATOMIC_RELAXED);
   uint32_t begin = end > DZN_COPY_RING ? end - DZN_COPY_RING : 0;
   unsigned shown = 0;
   for (uint32_t i = end; i-- > begin && shown < 32;) {
      const struct dzn_trace_copy *c = &dzn_copy_ring[i % DZN_COPY_RING];
      if (__atomic_load_n(&c->list, __ATOMIC_ACQUIRE) != list)
         continue;
      shown++;
      if (c->buffer) {
         D3D12_RESOURCE_DESC dd, sd;
         c->dst.pResource->lpVtbl->GetDesc(c->dst.pResource, &dd);
         c->src.pResource->lpVtbl->GetDesc(c->src.pResource, &sd);
         mesa_loge("dzn: copy (newest first) %u: buffer %llu bytes, dst %p+%llu of %llu, src %p+%llu of %llu", shown,
                   (unsigned long long)c->size, (void *)c->dst.pResource, (unsigned long long)c->dst_off, (unsigned long long)dd.Width,
                   (void *)c->src.pResource, (unsigned long long)c->src_off, (unsigned long long)sd.Width);
      } else {
         mesa_loge("dzn: copy (newest first) %u: texture", shown);
         dzn_probe_detail_CopyTextureRegion(&c->dst, c->x, c->y, c->z, &c->src, c->has_box ? &c->box : NULL);
      }
   }
   if (!shown)
      mesa_loge("dzn: no copies recorded on this command list among the last %u copies", DZN_COPY_RING);
}
