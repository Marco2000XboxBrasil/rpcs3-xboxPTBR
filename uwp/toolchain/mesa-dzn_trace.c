/* D3D12 command list call tracer for debugging Dozen on the Xbox (no D3D12 debug layer there).
 * dzn_trace_macros.h routes every ID3D12GraphicsCommandList*_X() macro call through dzn_trace_note(). */
#include <stdint.h>
#include "util/log.h"

void dzn_trace_note(const void *list, const char *method);
void dzn_trace_dump(const void *list, unsigned last);

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
   mesa_loge("dzn: %u D3D12 calls on this command list since its Reset (showing last %u):", count, last);
   unsigned skip = count > last ? count - last : 0, n = 0;
   for (uint32_t i = start; i != end; i++) {
      const struct dzn_trace_entry *e = &dzn_trace_ring[i % DZN_TRACE_RING];
      if (e->list != list || n++ < skip)
         continue;
      mesa_loge("dzn:   #%u %s", n - 1, e->method);
   }
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
