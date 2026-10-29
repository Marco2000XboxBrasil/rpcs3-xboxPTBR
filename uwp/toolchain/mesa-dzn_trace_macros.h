/* Generated from d3d12.h: route Dozen's command list calls through dzn_trace_note() and, for
 * calls that D3D12 validates on their own, replay them on a scratch list to find the one that
 * breaks the real list (Xbox UWP diagnostics, no debug layer there). */
#ifndef DZN_TRACE_MACROS_H
#define DZN_TRACE_MACROS_H
void dzn_trace_note(const void *list, const char *method);
void dzn_trace_copy_tex(const void *list, const D3D12_TEXTURE_COPY_LOCATION *dst, UINT x, UINT y, UINT z, const D3D12_TEXTURE_COPY_LOCATION *src, const D3D12_BOX *box);
void dzn_trace_check_barriers(const void *list, UINT n, const D3D12_RESOURCE_BARRIER *b);
void dzn_trace_copy_buf(const void *list, ID3D12Resource *dst, UINT64 dst_off, ID3D12Resource *src, UINT64 src_off, UINT64 size);
extern void *dzn_probe_list_;
void *dzn_probe_begin(void *list);
int dzn_probe_end(const char *method);
void dzn_probe_detail_ResourceBarrier(UINT n, const D3D12_RESOURCE_BARRIER *b);
void dzn_probe_detail_CopyTextureRegion(const D3D12_TEXTURE_COPY_LOCATION *dst, UINT x, UINT y, UINT z, const D3D12_TEXTURE_COPY_LOCATION *src, const D3D12_BOX *box);
void dzn_probe_detail_ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE rtv, const FLOAT *color, UINT n, const D3D12_RECT *rects);
void dzn_probe_detail_OMSetRenderTargets(UINT n, const D3D12_CPU_DESCRIPTOR_HANDLE *rtvs, BOOL single, const D3D12_CPU_DESCRIPTOR_HANDLE *dsv);
void dzn_probe_detail_IASetVertexBuffers(UINT start, UINT n, const D3D12_VERTEX_BUFFER_VIEW *v);
void dzn_probe_detail_RSSetViewports(UINT n, const D3D12_VIEWPORT *v);
void dzn_probe_detail_RSSetScissorRects(UINT n, const D3D12_RECT *r);

#undef ID3D12GraphicsCommandList_Close
#define ID3D12GraphicsCommandList_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList_Reset
#define ID3D12GraphicsCommandList_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList_ClearState
#define ID3D12GraphicsCommandList_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList_DrawInstanced
#define ID3D12GraphicsCommandList_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList_DrawIndexedInstanced
#define ID3D12GraphicsCommandList_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList_Dispatch
#define ID3D12GraphicsCommandList_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList_CopyBufferRegion
#define ID3D12GraphicsCommandList_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList_CopyTextureRegion
#define ID3D12GraphicsCommandList_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList_CopyResource
#define ID3D12GraphicsCommandList_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList_CopyTiles
#define ID3D12GraphicsCommandList_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList_ResolveSubresource
#define ID3D12GraphicsCommandList_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList_RSSetViewports
#define ID3D12GraphicsCommandList_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList_RSSetScissorRects
#define ID3D12GraphicsCommandList_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList_OMSetBlendFactor
#define ID3D12GraphicsCommandList_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList_OMSetStencilRef
#define ID3D12GraphicsCommandList_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList_SetPipelineState
#define ID3D12GraphicsCommandList_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList_ResourceBarrier
#define ID3D12GraphicsCommandList_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList_ExecuteBundle
#define ID3D12GraphicsCommandList_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList_SetDescriptorHeaps
#define ID3D12GraphicsCommandList_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList_SetComputeRootSignature
#define ID3D12GraphicsCommandList_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList_IASetIndexBuffer
#define ID3D12GraphicsCommandList_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList_IASetVertexBuffers
#define ID3D12GraphicsCommandList_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList_SOSetTargets
#define ID3D12GraphicsCommandList_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList_OMSetRenderTargets
#define ID3D12GraphicsCommandList_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList_ClearDepthStencilView
#define ID3D12GraphicsCommandList_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList_ClearRenderTargetView
#define ID3D12GraphicsCommandList_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList_DiscardResource
#define ID3D12GraphicsCommandList_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList_BeginQuery
#define ID3D12GraphicsCommandList_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList_EndQuery
#define ID3D12GraphicsCommandList_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList_ResolveQueryData
#define ID3D12GraphicsCommandList_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList_SetPredication
#define ID3D12GraphicsCommandList_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList_SetMarker
#define ID3D12GraphicsCommandList_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList_BeginEvent
#define ID3D12GraphicsCommandList_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList_EndEvent
#define ID3D12GraphicsCommandList_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList_ExecuteIndirect
#define ID3D12GraphicsCommandList_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList1_Close
#define ID3D12GraphicsCommandList1_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList1_Reset
#define ID3D12GraphicsCommandList1_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList1_ClearState
#define ID3D12GraphicsCommandList1_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList1_DrawInstanced
#define ID3D12GraphicsCommandList1_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList1_DrawIndexedInstanced
#define ID3D12GraphicsCommandList1_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList1_Dispatch
#define ID3D12GraphicsCommandList1_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList1_CopyBufferRegion
#define ID3D12GraphicsCommandList1_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList1_CopyTextureRegion
#define ID3D12GraphicsCommandList1_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList1_CopyResource
#define ID3D12GraphicsCommandList1_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList1_CopyTiles
#define ID3D12GraphicsCommandList1_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList1_ResolveSubresource
#define ID3D12GraphicsCommandList1_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList1_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList1_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList1_RSSetViewports
#define ID3D12GraphicsCommandList1_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList1_RSSetScissorRects
#define ID3D12GraphicsCommandList1_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList1_OMSetBlendFactor
#define ID3D12GraphicsCommandList1_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList1_OMSetStencilRef
#define ID3D12GraphicsCommandList1_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList1_SetPipelineState
#define ID3D12GraphicsCommandList1_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList1_ResourceBarrier
#define ID3D12GraphicsCommandList1_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList1_ExecuteBundle
#define ID3D12GraphicsCommandList1_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList1_SetDescriptorHeaps
#define ID3D12GraphicsCommandList1_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList1_SetComputeRootSignature
#define ID3D12GraphicsCommandList1_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList1_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList1_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList1_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList1_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList1_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList1_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList1_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList1_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList1_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList1_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList1_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList1_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList1_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList1_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList1_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList1_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList1_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList1_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList1_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList1_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList1_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList1_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList1_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList1_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList1_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList1_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList1_IASetIndexBuffer
#define ID3D12GraphicsCommandList1_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList1_IASetVertexBuffers
#define ID3D12GraphicsCommandList1_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList1_SOSetTargets
#define ID3D12GraphicsCommandList1_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList1_OMSetRenderTargets
#define ID3D12GraphicsCommandList1_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList1_ClearDepthStencilView
#define ID3D12GraphicsCommandList1_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList1_ClearRenderTargetView
#define ID3D12GraphicsCommandList1_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList1_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList1_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList1_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList1_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList1_DiscardResource
#define ID3D12GraphicsCommandList1_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList1_BeginQuery
#define ID3D12GraphicsCommandList1_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList1_EndQuery
#define ID3D12GraphicsCommandList1_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList1_ResolveQueryData
#define ID3D12GraphicsCommandList1_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList1_SetPredication
#define ID3D12GraphicsCommandList1_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList1_SetMarker
#define ID3D12GraphicsCommandList1_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList1_BeginEvent
#define ID3D12GraphicsCommandList1_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList1_EndEvent
#define ID3D12GraphicsCommandList1_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList1_ExecuteIndirect
#define ID3D12GraphicsCommandList1_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList1_AtomicCopyBufferUINT
#define ID3D12GraphicsCommandList1_AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT"), (This)->lpVtbl->AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList1_AtomicCopyBufferUINT64
#define ID3D12GraphicsCommandList1_AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT64"), (This)->lpVtbl->AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList1_OMSetDepthBounds
#define ID3D12GraphicsCommandList1_OMSetDepthBounds(This,Min,Max) (dzn_trace_note((This), "OMSetDepthBounds"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList1 *)dzn_probe_list_)->lpVtbl->OMSetDepthBounds(((ID3D12GraphicsCommandList1 *)dzn_probe_list_),Min,Max), dzn_probe_end("OMSetDepthBounds") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetDepthBounds(This,Min,Max))
#undef ID3D12GraphicsCommandList1_SetSamplePositions
#define ID3D12GraphicsCommandList1_SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions) (dzn_trace_note((This), "SetSamplePositions"), (This)->lpVtbl->SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions))
#undef ID3D12GraphicsCommandList1_ResolveSubresourceRegion
#define ID3D12GraphicsCommandList1_ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode) (dzn_trace_note((This), "ResolveSubresourceRegion"), (This)->lpVtbl->ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode))
#undef ID3D12GraphicsCommandList1_SetViewInstanceMask
#define ID3D12GraphicsCommandList1_SetViewInstanceMask(This,Mask) (dzn_trace_note((This), "SetViewInstanceMask"), (This)->lpVtbl->SetViewInstanceMask(This,Mask))
#undef ID3D12GraphicsCommandList2_Close
#define ID3D12GraphicsCommandList2_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList2_Reset
#define ID3D12GraphicsCommandList2_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList2_ClearState
#define ID3D12GraphicsCommandList2_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList2_DrawInstanced
#define ID3D12GraphicsCommandList2_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList2_DrawIndexedInstanced
#define ID3D12GraphicsCommandList2_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList2_Dispatch
#define ID3D12GraphicsCommandList2_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList2_CopyBufferRegion
#define ID3D12GraphicsCommandList2_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList2_CopyTextureRegion
#define ID3D12GraphicsCommandList2_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList2_CopyResource
#define ID3D12GraphicsCommandList2_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList2_CopyTiles
#define ID3D12GraphicsCommandList2_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList2_ResolveSubresource
#define ID3D12GraphicsCommandList2_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList2_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList2_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList2_RSSetViewports
#define ID3D12GraphicsCommandList2_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList2_RSSetScissorRects
#define ID3D12GraphicsCommandList2_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList2_OMSetBlendFactor
#define ID3D12GraphicsCommandList2_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList2_OMSetStencilRef
#define ID3D12GraphicsCommandList2_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList2_SetPipelineState
#define ID3D12GraphicsCommandList2_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList2_ResourceBarrier
#define ID3D12GraphicsCommandList2_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList2_ExecuteBundle
#define ID3D12GraphicsCommandList2_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList2_SetDescriptorHeaps
#define ID3D12GraphicsCommandList2_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList2_SetComputeRootSignature
#define ID3D12GraphicsCommandList2_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList2_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList2_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList2_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList2_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList2_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList2_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList2_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList2_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList2_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList2_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList2_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList2_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList2_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList2_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList2_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList2_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList2_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList2_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList2_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList2_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList2_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList2_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList2_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList2_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList2_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList2_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList2_IASetIndexBuffer
#define ID3D12GraphicsCommandList2_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList2_IASetVertexBuffers
#define ID3D12GraphicsCommandList2_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList2_SOSetTargets
#define ID3D12GraphicsCommandList2_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList2_OMSetRenderTargets
#define ID3D12GraphicsCommandList2_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList2_ClearDepthStencilView
#define ID3D12GraphicsCommandList2_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList2_ClearRenderTargetView
#define ID3D12GraphicsCommandList2_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList2_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList2_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList2_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList2_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList2_DiscardResource
#define ID3D12GraphicsCommandList2_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList2_BeginQuery
#define ID3D12GraphicsCommandList2_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList2_EndQuery
#define ID3D12GraphicsCommandList2_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList2_ResolveQueryData
#define ID3D12GraphicsCommandList2_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList2_SetPredication
#define ID3D12GraphicsCommandList2_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList2_SetMarker
#define ID3D12GraphicsCommandList2_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList2_BeginEvent
#define ID3D12GraphicsCommandList2_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList2_EndEvent
#define ID3D12GraphicsCommandList2_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList2_ExecuteIndirect
#define ID3D12GraphicsCommandList2_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList2_AtomicCopyBufferUINT
#define ID3D12GraphicsCommandList2_AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT"), (This)->lpVtbl->AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList2_AtomicCopyBufferUINT64
#define ID3D12GraphicsCommandList2_AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT64"), (This)->lpVtbl->AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList2_OMSetDepthBounds
#define ID3D12GraphicsCommandList2_OMSetDepthBounds(This,Min,Max) (dzn_trace_note((This), "OMSetDepthBounds"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList2 *)dzn_probe_list_)->lpVtbl->OMSetDepthBounds(((ID3D12GraphicsCommandList2 *)dzn_probe_list_),Min,Max), dzn_probe_end("OMSetDepthBounds") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetDepthBounds(This,Min,Max))
#undef ID3D12GraphicsCommandList2_SetSamplePositions
#define ID3D12GraphicsCommandList2_SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions) (dzn_trace_note((This), "SetSamplePositions"), (This)->lpVtbl->SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions))
#undef ID3D12GraphicsCommandList2_ResolveSubresourceRegion
#define ID3D12GraphicsCommandList2_ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode) (dzn_trace_note((This), "ResolveSubresourceRegion"), (This)->lpVtbl->ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode))
#undef ID3D12GraphicsCommandList2_SetViewInstanceMask
#define ID3D12GraphicsCommandList2_SetViewInstanceMask(This,Mask) (dzn_trace_note((This), "SetViewInstanceMask"), (This)->lpVtbl->SetViewInstanceMask(This,Mask))
#undef ID3D12GraphicsCommandList2_WriteBufferImmediate
#define ID3D12GraphicsCommandList2_WriteBufferImmediate(This,Count,pParams,pModes) (dzn_trace_note((This), "WriteBufferImmediate"), (This)->lpVtbl->WriteBufferImmediate(This,Count,pParams,pModes))
#undef ID3D12GraphicsCommandList3_Close
#define ID3D12GraphicsCommandList3_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList3_Reset
#define ID3D12GraphicsCommandList3_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList3_ClearState
#define ID3D12GraphicsCommandList3_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList3_DrawInstanced
#define ID3D12GraphicsCommandList3_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList3_DrawIndexedInstanced
#define ID3D12GraphicsCommandList3_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList3_Dispatch
#define ID3D12GraphicsCommandList3_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList3_CopyBufferRegion
#define ID3D12GraphicsCommandList3_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList3_CopyTextureRegion
#define ID3D12GraphicsCommandList3_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList3_CopyResource
#define ID3D12GraphicsCommandList3_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList3_CopyTiles
#define ID3D12GraphicsCommandList3_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList3_ResolveSubresource
#define ID3D12GraphicsCommandList3_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList3_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList3_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList3_RSSetViewports
#define ID3D12GraphicsCommandList3_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList3_RSSetScissorRects
#define ID3D12GraphicsCommandList3_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList3_OMSetBlendFactor
#define ID3D12GraphicsCommandList3_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList3_OMSetStencilRef
#define ID3D12GraphicsCommandList3_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList3_SetPipelineState
#define ID3D12GraphicsCommandList3_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList3_ResourceBarrier
#define ID3D12GraphicsCommandList3_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList3_ExecuteBundle
#define ID3D12GraphicsCommandList3_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList3_SetDescriptorHeaps
#define ID3D12GraphicsCommandList3_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList3_SetComputeRootSignature
#define ID3D12GraphicsCommandList3_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList3_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList3_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList3_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList3_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList3_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList3_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList3_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList3_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList3_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList3_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList3_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList3_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList3_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList3_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList3_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList3_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList3_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList3_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList3_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList3_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList3_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList3_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList3_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList3_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList3_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList3_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList3_IASetIndexBuffer
#define ID3D12GraphicsCommandList3_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList3_IASetVertexBuffers
#define ID3D12GraphicsCommandList3_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList3_SOSetTargets
#define ID3D12GraphicsCommandList3_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList3_OMSetRenderTargets
#define ID3D12GraphicsCommandList3_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList3_ClearDepthStencilView
#define ID3D12GraphicsCommandList3_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList3_ClearRenderTargetView
#define ID3D12GraphicsCommandList3_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList3_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList3_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList3_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList3_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList3_DiscardResource
#define ID3D12GraphicsCommandList3_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList3_BeginQuery
#define ID3D12GraphicsCommandList3_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList3_EndQuery
#define ID3D12GraphicsCommandList3_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList3_ResolveQueryData
#define ID3D12GraphicsCommandList3_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList3_SetPredication
#define ID3D12GraphicsCommandList3_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList3_SetMarker
#define ID3D12GraphicsCommandList3_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList3_BeginEvent
#define ID3D12GraphicsCommandList3_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList3_EndEvent
#define ID3D12GraphicsCommandList3_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList3_ExecuteIndirect
#define ID3D12GraphicsCommandList3_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList3_AtomicCopyBufferUINT
#define ID3D12GraphicsCommandList3_AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT"), (This)->lpVtbl->AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList3_AtomicCopyBufferUINT64
#define ID3D12GraphicsCommandList3_AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT64"), (This)->lpVtbl->AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList3_OMSetDepthBounds
#define ID3D12GraphicsCommandList3_OMSetDepthBounds(This,Min,Max) (dzn_trace_note((This), "OMSetDepthBounds"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList3 *)dzn_probe_list_)->lpVtbl->OMSetDepthBounds(((ID3D12GraphicsCommandList3 *)dzn_probe_list_),Min,Max), dzn_probe_end("OMSetDepthBounds") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetDepthBounds(This,Min,Max))
#undef ID3D12GraphicsCommandList3_SetSamplePositions
#define ID3D12GraphicsCommandList3_SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions) (dzn_trace_note((This), "SetSamplePositions"), (This)->lpVtbl->SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions))
#undef ID3D12GraphicsCommandList3_ResolveSubresourceRegion
#define ID3D12GraphicsCommandList3_ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode) (dzn_trace_note((This), "ResolveSubresourceRegion"), (This)->lpVtbl->ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode))
#undef ID3D12GraphicsCommandList3_SetViewInstanceMask
#define ID3D12GraphicsCommandList3_SetViewInstanceMask(This,Mask) (dzn_trace_note((This), "SetViewInstanceMask"), (This)->lpVtbl->SetViewInstanceMask(This,Mask))
#undef ID3D12GraphicsCommandList3_WriteBufferImmediate
#define ID3D12GraphicsCommandList3_WriteBufferImmediate(This,Count,pParams,pModes) (dzn_trace_note((This), "WriteBufferImmediate"), (This)->lpVtbl->WriteBufferImmediate(This,Count,pParams,pModes))
#undef ID3D12GraphicsCommandList3_SetProtectedResourceSession
#define ID3D12GraphicsCommandList3_SetProtectedResourceSession(This,pProtectedResourceSession) (dzn_trace_note((This), "SetProtectedResourceSession"), (This)->lpVtbl->SetProtectedResourceSession(This,pProtectedResourceSession))
#undef ID3D12GraphicsCommandList4_Close
#define ID3D12GraphicsCommandList4_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList4_Reset
#define ID3D12GraphicsCommandList4_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList4_ClearState
#define ID3D12GraphicsCommandList4_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList4_DrawInstanced
#define ID3D12GraphicsCommandList4_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList4_DrawIndexedInstanced
#define ID3D12GraphicsCommandList4_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList4_Dispatch
#define ID3D12GraphicsCommandList4_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList4_CopyBufferRegion
#define ID3D12GraphicsCommandList4_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList4_CopyTextureRegion
#define ID3D12GraphicsCommandList4_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList4_CopyResource
#define ID3D12GraphicsCommandList4_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList4_CopyTiles
#define ID3D12GraphicsCommandList4_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList4_ResolveSubresource
#define ID3D12GraphicsCommandList4_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList4_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList4_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList4_RSSetViewports
#define ID3D12GraphicsCommandList4_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList4_RSSetScissorRects
#define ID3D12GraphicsCommandList4_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList4_OMSetBlendFactor
#define ID3D12GraphicsCommandList4_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList4_OMSetStencilRef
#define ID3D12GraphicsCommandList4_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList4_SetPipelineState
#define ID3D12GraphicsCommandList4_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList4_ResourceBarrier
#define ID3D12GraphicsCommandList4_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList4_ExecuteBundle
#define ID3D12GraphicsCommandList4_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList4_SetDescriptorHeaps
#define ID3D12GraphicsCommandList4_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList4_SetComputeRootSignature
#define ID3D12GraphicsCommandList4_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList4_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList4_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList4_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList4_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList4_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList4_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList4_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList4_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList4_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList4_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList4_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList4_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList4_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList4_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList4_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList4_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList4_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList4_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList4_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList4_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList4_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList4_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList4_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList4_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList4_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList4_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList4_IASetIndexBuffer
#define ID3D12GraphicsCommandList4_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList4_IASetVertexBuffers
#define ID3D12GraphicsCommandList4_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList4_SOSetTargets
#define ID3D12GraphicsCommandList4_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList4_OMSetRenderTargets
#define ID3D12GraphicsCommandList4_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList4_ClearDepthStencilView
#define ID3D12GraphicsCommandList4_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList4_ClearRenderTargetView
#define ID3D12GraphicsCommandList4_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList4_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList4_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList4_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList4_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList4_DiscardResource
#define ID3D12GraphicsCommandList4_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList4_BeginQuery
#define ID3D12GraphicsCommandList4_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList4_EndQuery
#define ID3D12GraphicsCommandList4_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList4_ResolveQueryData
#define ID3D12GraphicsCommandList4_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList4_SetPredication
#define ID3D12GraphicsCommandList4_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList4_SetMarker
#define ID3D12GraphicsCommandList4_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList4_BeginEvent
#define ID3D12GraphicsCommandList4_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList4_EndEvent
#define ID3D12GraphicsCommandList4_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList4_ExecuteIndirect
#define ID3D12GraphicsCommandList4_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList4_AtomicCopyBufferUINT
#define ID3D12GraphicsCommandList4_AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT"), (This)->lpVtbl->AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList4_AtomicCopyBufferUINT64
#define ID3D12GraphicsCommandList4_AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT64"), (This)->lpVtbl->AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList4_OMSetDepthBounds
#define ID3D12GraphicsCommandList4_OMSetDepthBounds(This,Min,Max) (dzn_trace_note((This), "OMSetDepthBounds"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList4 *)dzn_probe_list_)->lpVtbl->OMSetDepthBounds(((ID3D12GraphicsCommandList4 *)dzn_probe_list_),Min,Max), dzn_probe_end("OMSetDepthBounds") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetDepthBounds(This,Min,Max))
#undef ID3D12GraphicsCommandList4_SetSamplePositions
#define ID3D12GraphicsCommandList4_SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions) (dzn_trace_note((This), "SetSamplePositions"), (This)->lpVtbl->SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions))
#undef ID3D12GraphicsCommandList4_ResolveSubresourceRegion
#define ID3D12GraphicsCommandList4_ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode) (dzn_trace_note((This), "ResolveSubresourceRegion"), (This)->lpVtbl->ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode))
#undef ID3D12GraphicsCommandList4_SetViewInstanceMask
#define ID3D12GraphicsCommandList4_SetViewInstanceMask(This,Mask) (dzn_trace_note((This), "SetViewInstanceMask"), (This)->lpVtbl->SetViewInstanceMask(This,Mask))
#undef ID3D12GraphicsCommandList4_WriteBufferImmediate
#define ID3D12GraphicsCommandList4_WriteBufferImmediate(This,Count,pParams,pModes) (dzn_trace_note((This), "WriteBufferImmediate"), (This)->lpVtbl->WriteBufferImmediate(This,Count,pParams,pModes))
#undef ID3D12GraphicsCommandList4_SetProtectedResourceSession
#define ID3D12GraphicsCommandList4_SetProtectedResourceSession(This,pProtectedResourceSession) (dzn_trace_note((This), "SetProtectedResourceSession"), (This)->lpVtbl->SetProtectedResourceSession(This,pProtectedResourceSession))
#undef ID3D12GraphicsCommandList4_BeginRenderPass
#define ID3D12GraphicsCommandList4_BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags) (dzn_trace_note((This), "BeginRenderPass"), (This)->lpVtbl->BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags))
#undef ID3D12GraphicsCommandList4_EndRenderPass
#define ID3D12GraphicsCommandList4_EndRenderPass(This) (dzn_trace_note((This), "EndRenderPass"), (This)->lpVtbl->EndRenderPass(This))
#undef ID3D12GraphicsCommandList4_InitializeMetaCommand
#define ID3D12GraphicsCommandList4_InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes) (dzn_trace_note((This), "InitializeMetaCommand"), (This)->lpVtbl->InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList4_ExecuteMetaCommand
#define ID3D12GraphicsCommandList4_ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes) (dzn_trace_note((This), "ExecuteMetaCommand"), (This)->lpVtbl->ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList4_BuildRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList4_BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs) (dzn_trace_note((This), "BuildRaytracingAccelerationStructure"), (This)->lpVtbl->BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs))
#undef ID3D12GraphicsCommandList4_EmitRaytracingAccelerationStructurePostbuildInfo
#define ID3D12GraphicsCommandList4_EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData) (dzn_trace_note((This), "EmitRaytracingAccelerationStructurePostbuildInfo"), (This)->lpVtbl->EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData))
#undef ID3D12GraphicsCommandList4_CopyRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList4_CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode) (dzn_trace_note((This), "CopyRaytracingAccelerationStructure"), (This)->lpVtbl->CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode))
#undef ID3D12GraphicsCommandList4_SetPipelineState1
#define ID3D12GraphicsCommandList4_SetPipelineState1(This,pStateObject) (dzn_trace_note((This), "SetPipelineState1"), (This)->lpVtbl->SetPipelineState1(This,pStateObject))
#undef ID3D12GraphicsCommandList4_DispatchRays
#define ID3D12GraphicsCommandList4_DispatchRays(This,pDesc) (dzn_trace_note((This), "DispatchRays"), (This)->lpVtbl->DispatchRays(This,pDesc))
#undef ID3D12GraphicsCommandList5_Close
#define ID3D12GraphicsCommandList5_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList5_Reset
#define ID3D12GraphicsCommandList5_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList5_ClearState
#define ID3D12GraphicsCommandList5_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList5_DrawInstanced
#define ID3D12GraphicsCommandList5_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList5_DrawIndexedInstanced
#define ID3D12GraphicsCommandList5_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList5_Dispatch
#define ID3D12GraphicsCommandList5_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList5_CopyBufferRegion
#define ID3D12GraphicsCommandList5_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList5_CopyTextureRegion
#define ID3D12GraphicsCommandList5_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList5_CopyResource
#define ID3D12GraphicsCommandList5_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList5_CopyTiles
#define ID3D12GraphicsCommandList5_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList5_ResolveSubresource
#define ID3D12GraphicsCommandList5_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList5_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList5_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList5_RSSetViewports
#define ID3D12GraphicsCommandList5_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList5_RSSetScissorRects
#define ID3D12GraphicsCommandList5_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList5_OMSetBlendFactor
#define ID3D12GraphicsCommandList5_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList5_OMSetStencilRef
#define ID3D12GraphicsCommandList5_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList5_SetPipelineState
#define ID3D12GraphicsCommandList5_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList5_ResourceBarrier
#define ID3D12GraphicsCommandList5_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList5_ExecuteBundle
#define ID3D12GraphicsCommandList5_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList5_SetDescriptorHeaps
#define ID3D12GraphicsCommandList5_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList5_SetComputeRootSignature
#define ID3D12GraphicsCommandList5_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList5_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList5_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList5_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList5_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList5_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList5_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList5_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList5_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList5_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList5_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList5_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList5_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList5_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList5_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList5_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList5_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList5_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList5_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList5_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList5_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList5_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList5_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList5_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList5_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList5_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList5_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList5_IASetIndexBuffer
#define ID3D12GraphicsCommandList5_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList5_IASetVertexBuffers
#define ID3D12GraphicsCommandList5_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList5_SOSetTargets
#define ID3D12GraphicsCommandList5_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList5_OMSetRenderTargets
#define ID3D12GraphicsCommandList5_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList5_ClearDepthStencilView
#define ID3D12GraphicsCommandList5_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList5_ClearRenderTargetView
#define ID3D12GraphicsCommandList5_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList5_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList5_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList5_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList5_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList5_DiscardResource
#define ID3D12GraphicsCommandList5_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList5_BeginQuery
#define ID3D12GraphicsCommandList5_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList5_EndQuery
#define ID3D12GraphicsCommandList5_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList5_ResolveQueryData
#define ID3D12GraphicsCommandList5_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList5_SetPredication
#define ID3D12GraphicsCommandList5_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList5_SetMarker
#define ID3D12GraphicsCommandList5_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList5_BeginEvent
#define ID3D12GraphicsCommandList5_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList5_EndEvent
#define ID3D12GraphicsCommandList5_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList5_ExecuteIndirect
#define ID3D12GraphicsCommandList5_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList5_AtomicCopyBufferUINT
#define ID3D12GraphicsCommandList5_AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT"), (This)->lpVtbl->AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList5_AtomicCopyBufferUINT64
#define ID3D12GraphicsCommandList5_AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT64"), (This)->lpVtbl->AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList5_OMSetDepthBounds
#define ID3D12GraphicsCommandList5_OMSetDepthBounds(This,Min,Max) (dzn_trace_note((This), "OMSetDepthBounds"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList5 *)dzn_probe_list_)->lpVtbl->OMSetDepthBounds(((ID3D12GraphicsCommandList5 *)dzn_probe_list_),Min,Max), dzn_probe_end("OMSetDepthBounds") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetDepthBounds(This,Min,Max))
#undef ID3D12GraphicsCommandList5_SetSamplePositions
#define ID3D12GraphicsCommandList5_SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions) (dzn_trace_note((This), "SetSamplePositions"), (This)->lpVtbl->SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions))
#undef ID3D12GraphicsCommandList5_ResolveSubresourceRegion
#define ID3D12GraphicsCommandList5_ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode) (dzn_trace_note((This), "ResolveSubresourceRegion"), (This)->lpVtbl->ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode))
#undef ID3D12GraphicsCommandList5_SetViewInstanceMask
#define ID3D12GraphicsCommandList5_SetViewInstanceMask(This,Mask) (dzn_trace_note((This), "SetViewInstanceMask"), (This)->lpVtbl->SetViewInstanceMask(This,Mask))
#undef ID3D12GraphicsCommandList5_WriteBufferImmediate
#define ID3D12GraphicsCommandList5_WriteBufferImmediate(This,Count,pParams,pModes) (dzn_trace_note((This), "WriteBufferImmediate"), (This)->lpVtbl->WriteBufferImmediate(This,Count,pParams,pModes))
#undef ID3D12GraphicsCommandList5_SetProtectedResourceSession
#define ID3D12GraphicsCommandList5_SetProtectedResourceSession(This,pProtectedResourceSession) (dzn_trace_note((This), "SetProtectedResourceSession"), (This)->lpVtbl->SetProtectedResourceSession(This,pProtectedResourceSession))
#undef ID3D12GraphicsCommandList5_BeginRenderPass
#define ID3D12GraphicsCommandList5_BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags) (dzn_trace_note((This), "BeginRenderPass"), (This)->lpVtbl->BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags))
#undef ID3D12GraphicsCommandList5_EndRenderPass
#define ID3D12GraphicsCommandList5_EndRenderPass(This) (dzn_trace_note((This), "EndRenderPass"), (This)->lpVtbl->EndRenderPass(This))
#undef ID3D12GraphicsCommandList5_InitializeMetaCommand
#define ID3D12GraphicsCommandList5_InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes) (dzn_trace_note((This), "InitializeMetaCommand"), (This)->lpVtbl->InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList5_ExecuteMetaCommand
#define ID3D12GraphicsCommandList5_ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes) (dzn_trace_note((This), "ExecuteMetaCommand"), (This)->lpVtbl->ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList5_BuildRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList5_BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs) (dzn_trace_note((This), "BuildRaytracingAccelerationStructure"), (This)->lpVtbl->BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs))
#undef ID3D12GraphicsCommandList5_EmitRaytracingAccelerationStructurePostbuildInfo
#define ID3D12GraphicsCommandList5_EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData) (dzn_trace_note((This), "EmitRaytracingAccelerationStructurePostbuildInfo"), (This)->lpVtbl->EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData))
#undef ID3D12GraphicsCommandList5_CopyRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList5_CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode) (dzn_trace_note((This), "CopyRaytracingAccelerationStructure"), (This)->lpVtbl->CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode))
#undef ID3D12GraphicsCommandList5_SetPipelineState1
#define ID3D12GraphicsCommandList5_SetPipelineState1(This,pStateObject) (dzn_trace_note((This), "SetPipelineState1"), (This)->lpVtbl->SetPipelineState1(This,pStateObject))
#undef ID3D12GraphicsCommandList5_DispatchRays
#define ID3D12GraphicsCommandList5_DispatchRays(This,pDesc) (dzn_trace_note((This), "DispatchRays"), (This)->lpVtbl->DispatchRays(This,pDesc))
#undef ID3D12GraphicsCommandList5_RSSetShadingRate
#define ID3D12GraphicsCommandList5_RSSetShadingRate(This,baseShadingRate,combiners) (dzn_trace_note((This), "RSSetShadingRate"), (This)->lpVtbl->RSSetShadingRate(This,baseShadingRate,combiners))
#undef ID3D12GraphicsCommandList5_RSSetShadingRateImage
#define ID3D12GraphicsCommandList5_RSSetShadingRateImage(This,shadingRateImage) (dzn_trace_note((This), "RSSetShadingRateImage"), (This)->lpVtbl->RSSetShadingRateImage(This,shadingRateImage))
#undef ID3D12GraphicsCommandList6_Close
#define ID3D12GraphicsCommandList6_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList6_Reset
#define ID3D12GraphicsCommandList6_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList6_ClearState
#define ID3D12GraphicsCommandList6_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList6_DrawInstanced
#define ID3D12GraphicsCommandList6_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList6_DrawIndexedInstanced
#define ID3D12GraphicsCommandList6_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList6_Dispatch
#define ID3D12GraphicsCommandList6_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList6_CopyBufferRegion
#define ID3D12GraphicsCommandList6_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList6_CopyTextureRegion
#define ID3D12GraphicsCommandList6_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList6_CopyResource
#define ID3D12GraphicsCommandList6_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList6_CopyTiles
#define ID3D12GraphicsCommandList6_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList6_ResolveSubresource
#define ID3D12GraphicsCommandList6_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList6_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList6_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList6_RSSetViewports
#define ID3D12GraphicsCommandList6_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList6_RSSetScissorRects
#define ID3D12GraphicsCommandList6_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList6_OMSetBlendFactor
#define ID3D12GraphicsCommandList6_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList6_OMSetStencilRef
#define ID3D12GraphicsCommandList6_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList6_SetPipelineState
#define ID3D12GraphicsCommandList6_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList6_ResourceBarrier
#define ID3D12GraphicsCommandList6_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList6_ExecuteBundle
#define ID3D12GraphicsCommandList6_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList6_SetDescriptorHeaps
#define ID3D12GraphicsCommandList6_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList6_SetComputeRootSignature
#define ID3D12GraphicsCommandList6_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList6_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList6_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList6_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList6_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList6_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList6_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList6_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList6_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList6_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList6_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList6_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList6_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList6_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList6_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList6_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList6_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList6_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList6_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList6_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList6_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList6_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList6_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList6_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList6_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList6_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList6_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList6_IASetIndexBuffer
#define ID3D12GraphicsCommandList6_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList6_IASetVertexBuffers
#define ID3D12GraphicsCommandList6_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList6_SOSetTargets
#define ID3D12GraphicsCommandList6_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList6_OMSetRenderTargets
#define ID3D12GraphicsCommandList6_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList6_ClearDepthStencilView
#define ID3D12GraphicsCommandList6_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList6_ClearRenderTargetView
#define ID3D12GraphicsCommandList6_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList6_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList6_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList6_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList6_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList6_DiscardResource
#define ID3D12GraphicsCommandList6_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList6_BeginQuery
#define ID3D12GraphicsCommandList6_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList6_EndQuery
#define ID3D12GraphicsCommandList6_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList6_ResolveQueryData
#define ID3D12GraphicsCommandList6_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList6_SetPredication
#define ID3D12GraphicsCommandList6_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList6_SetMarker
#define ID3D12GraphicsCommandList6_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList6_BeginEvent
#define ID3D12GraphicsCommandList6_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList6_EndEvent
#define ID3D12GraphicsCommandList6_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList6_ExecuteIndirect
#define ID3D12GraphicsCommandList6_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList6_AtomicCopyBufferUINT
#define ID3D12GraphicsCommandList6_AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT"), (This)->lpVtbl->AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList6_AtomicCopyBufferUINT64
#define ID3D12GraphicsCommandList6_AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT64"), (This)->lpVtbl->AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList6_OMSetDepthBounds
#define ID3D12GraphicsCommandList6_OMSetDepthBounds(This,Min,Max) (dzn_trace_note((This), "OMSetDepthBounds"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList6 *)dzn_probe_list_)->lpVtbl->OMSetDepthBounds(((ID3D12GraphicsCommandList6 *)dzn_probe_list_),Min,Max), dzn_probe_end("OMSetDepthBounds") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetDepthBounds(This,Min,Max))
#undef ID3D12GraphicsCommandList6_SetSamplePositions
#define ID3D12GraphicsCommandList6_SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions) (dzn_trace_note((This), "SetSamplePositions"), (This)->lpVtbl->SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions))
#undef ID3D12GraphicsCommandList6_ResolveSubresourceRegion
#define ID3D12GraphicsCommandList6_ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode) (dzn_trace_note((This), "ResolveSubresourceRegion"), (This)->lpVtbl->ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode))
#undef ID3D12GraphicsCommandList6_SetViewInstanceMask
#define ID3D12GraphicsCommandList6_SetViewInstanceMask(This,Mask) (dzn_trace_note((This), "SetViewInstanceMask"), (This)->lpVtbl->SetViewInstanceMask(This,Mask))
#undef ID3D12GraphicsCommandList6_WriteBufferImmediate
#define ID3D12GraphicsCommandList6_WriteBufferImmediate(This,Count,pParams,pModes) (dzn_trace_note((This), "WriteBufferImmediate"), (This)->lpVtbl->WriteBufferImmediate(This,Count,pParams,pModes))
#undef ID3D12GraphicsCommandList6_SetProtectedResourceSession
#define ID3D12GraphicsCommandList6_SetProtectedResourceSession(This,pProtectedResourceSession) (dzn_trace_note((This), "SetProtectedResourceSession"), (This)->lpVtbl->SetProtectedResourceSession(This,pProtectedResourceSession))
#undef ID3D12GraphicsCommandList6_BeginRenderPass
#define ID3D12GraphicsCommandList6_BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags) (dzn_trace_note((This), "BeginRenderPass"), (This)->lpVtbl->BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags))
#undef ID3D12GraphicsCommandList6_EndRenderPass
#define ID3D12GraphicsCommandList6_EndRenderPass(This) (dzn_trace_note((This), "EndRenderPass"), (This)->lpVtbl->EndRenderPass(This))
#undef ID3D12GraphicsCommandList6_InitializeMetaCommand
#define ID3D12GraphicsCommandList6_InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes) (dzn_trace_note((This), "InitializeMetaCommand"), (This)->lpVtbl->InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList6_ExecuteMetaCommand
#define ID3D12GraphicsCommandList6_ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes) (dzn_trace_note((This), "ExecuteMetaCommand"), (This)->lpVtbl->ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList6_BuildRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList6_BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs) (dzn_trace_note((This), "BuildRaytracingAccelerationStructure"), (This)->lpVtbl->BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs))
#undef ID3D12GraphicsCommandList6_EmitRaytracingAccelerationStructurePostbuildInfo
#define ID3D12GraphicsCommandList6_EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData) (dzn_trace_note((This), "EmitRaytracingAccelerationStructurePostbuildInfo"), (This)->lpVtbl->EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData))
#undef ID3D12GraphicsCommandList6_CopyRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList6_CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode) (dzn_trace_note((This), "CopyRaytracingAccelerationStructure"), (This)->lpVtbl->CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode))
#undef ID3D12GraphicsCommandList6_SetPipelineState1
#define ID3D12GraphicsCommandList6_SetPipelineState1(This,pStateObject) (dzn_trace_note((This), "SetPipelineState1"), (This)->lpVtbl->SetPipelineState1(This,pStateObject))
#undef ID3D12GraphicsCommandList6_DispatchRays
#define ID3D12GraphicsCommandList6_DispatchRays(This,pDesc) (dzn_trace_note((This), "DispatchRays"), (This)->lpVtbl->DispatchRays(This,pDesc))
#undef ID3D12GraphicsCommandList6_RSSetShadingRate
#define ID3D12GraphicsCommandList6_RSSetShadingRate(This,baseShadingRate,combiners) (dzn_trace_note((This), "RSSetShadingRate"), (This)->lpVtbl->RSSetShadingRate(This,baseShadingRate,combiners))
#undef ID3D12GraphicsCommandList6_RSSetShadingRateImage
#define ID3D12GraphicsCommandList6_RSSetShadingRateImage(This,shadingRateImage) (dzn_trace_note((This), "RSSetShadingRateImage"), (This)->lpVtbl->RSSetShadingRateImage(This,shadingRateImage))
#undef ID3D12GraphicsCommandList6_DispatchMesh
#define ID3D12GraphicsCommandList6_DispatchMesh(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "DispatchMesh"), (This)->lpVtbl->DispatchMesh(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList7_Close
#define ID3D12GraphicsCommandList7_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList7_Reset
#define ID3D12GraphicsCommandList7_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList7_ClearState
#define ID3D12GraphicsCommandList7_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList7_DrawInstanced
#define ID3D12GraphicsCommandList7_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList7_DrawIndexedInstanced
#define ID3D12GraphicsCommandList7_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList7_Dispatch
#define ID3D12GraphicsCommandList7_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList7_CopyBufferRegion
#define ID3D12GraphicsCommandList7_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList7_CopyTextureRegion
#define ID3D12GraphicsCommandList7_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList7_CopyResource
#define ID3D12GraphicsCommandList7_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList7_CopyTiles
#define ID3D12GraphicsCommandList7_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList7_ResolveSubresource
#define ID3D12GraphicsCommandList7_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList7_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList7_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList7_RSSetViewports
#define ID3D12GraphicsCommandList7_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList7_RSSetScissorRects
#define ID3D12GraphicsCommandList7_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList7_OMSetBlendFactor
#define ID3D12GraphicsCommandList7_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList7_OMSetStencilRef
#define ID3D12GraphicsCommandList7_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList7_SetPipelineState
#define ID3D12GraphicsCommandList7_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList7_ResourceBarrier
#define ID3D12GraphicsCommandList7_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList7_ExecuteBundle
#define ID3D12GraphicsCommandList7_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList7_SetDescriptorHeaps
#define ID3D12GraphicsCommandList7_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList7_SetComputeRootSignature
#define ID3D12GraphicsCommandList7_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList7_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList7_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList7_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList7_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList7_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList7_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList7_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList7_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList7_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList7_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList7_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList7_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList7_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList7_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList7_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList7_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList7_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList7_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList7_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList7_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList7_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList7_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList7_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList7_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList7_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList7_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList7_IASetIndexBuffer
#define ID3D12GraphicsCommandList7_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList7_IASetVertexBuffers
#define ID3D12GraphicsCommandList7_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList7_SOSetTargets
#define ID3D12GraphicsCommandList7_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList7_OMSetRenderTargets
#define ID3D12GraphicsCommandList7_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList7_ClearDepthStencilView
#define ID3D12GraphicsCommandList7_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList7_ClearRenderTargetView
#define ID3D12GraphicsCommandList7_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList7_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList7_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList7_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList7_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList7_DiscardResource
#define ID3D12GraphicsCommandList7_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList7_BeginQuery
#define ID3D12GraphicsCommandList7_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList7_EndQuery
#define ID3D12GraphicsCommandList7_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList7_ResolveQueryData
#define ID3D12GraphicsCommandList7_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList7_SetPredication
#define ID3D12GraphicsCommandList7_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList7_SetMarker
#define ID3D12GraphicsCommandList7_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList7_BeginEvent
#define ID3D12GraphicsCommandList7_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList7_EndEvent
#define ID3D12GraphicsCommandList7_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList7_ExecuteIndirect
#define ID3D12GraphicsCommandList7_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList7_AtomicCopyBufferUINT
#define ID3D12GraphicsCommandList7_AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT"), (This)->lpVtbl->AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList7_AtomicCopyBufferUINT64
#define ID3D12GraphicsCommandList7_AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT64"), (This)->lpVtbl->AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList7_OMSetDepthBounds
#define ID3D12GraphicsCommandList7_OMSetDepthBounds(This,Min,Max) (dzn_trace_note((This), "OMSetDepthBounds"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList7 *)dzn_probe_list_)->lpVtbl->OMSetDepthBounds(((ID3D12GraphicsCommandList7 *)dzn_probe_list_),Min,Max), dzn_probe_end("OMSetDepthBounds") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetDepthBounds(This,Min,Max))
#undef ID3D12GraphicsCommandList7_SetSamplePositions
#define ID3D12GraphicsCommandList7_SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions) (dzn_trace_note((This), "SetSamplePositions"), (This)->lpVtbl->SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions))
#undef ID3D12GraphicsCommandList7_ResolveSubresourceRegion
#define ID3D12GraphicsCommandList7_ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode) (dzn_trace_note((This), "ResolveSubresourceRegion"), (This)->lpVtbl->ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode))
#undef ID3D12GraphicsCommandList7_SetViewInstanceMask
#define ID3D12GraphicsCommandList7_SetViewInstanceMask(This,Mask) (dzn_trace_note((This), "SetViewInstanceMask"), (This)->lpVtbl->SetViewInstanceMask(This,Mask))
#undef ID3D12GraphicsCommandList7_WriteBufferImmediate
#define ID3D12GraphicsCommandList7_WriteBufferImmediate(This,Count,pParams,pModes) (dzn_trace_note((This), "WriteBufferImmediate"), (This)->lpVtbl->WriteBufferImmediate(This,Count,pParams,pModes))
#undef ID3D12GraphicsCommandList7_SetProtectedResourceSession
#define ID3D12GraphicsCommandList7_SetProtectedResourceSession(This,pProtectedResourceSession) (dzn_trace_note((This), "SetProtectedResourceSession"), (This)->lpVtbl->SetProtectedResourceSession(This,pProtectedResourceSession))
#undef ID3D12GraphicsCommandList7_BeginRenderPass
#define ID3D12GraphicsCommandList7_BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags) (dzn_trace_note((This), "BeginRenderPass"), (This)->lpVtbl->BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags))
#undef ID3D12GraphicsCommandList7_EndRenderPass
#define ID3D12GraphicsCommandList7_EndRenderPass(This) (dzn_trace_note((This), "EndRenderPass"), (This)->lpVtbl->EndRenderPass(This))
#undef ID3D12GraphicsCommandList7_InitializeMetaCommand
#define ID3D12GraphicsCommandList7_InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes) (dzn_trace_note((This), "InitializeMetaCommand"), (This)->lpVtbl->InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList7_ExecuteMetaCommand
#define ID3D12GraphicsCommandList7_ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes) (dzn_trace_note((This), "ExecuteMetaCommand"), (This)->lpVtbl->ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList7_BuildRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList7_BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs) (dzn_trace_note((This), "BuildRaytracingAccelerationStructure"), (This)->lpVtbl->BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs))
#undef ID3D12GraphicsCommandList7_EmitRaytracingAccelerationStructurePostbuildInfo
#define ID3D12GraphicsCommandList7_EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData) (dzn_trace_note((This), "EmitRaytracingAccelerationStructurePostbuildInfo"), (This)->lpVtbl->EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData))
#undef ID3D12GraphicsCommandList7_CopyRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList7_CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode) (dzn_trace_note((This), "CopyRaytracingAccelerationStructure"), (This)->lpVtbl->CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode))
#undef ID3D12GraphicsCommandList7_SetPipelineState1
#define ID3D12GraphicsCommandList7_SetPipelineState1(This,pStateObject) (dzn_trace_note((This), "SetPipelineState1"), (This)->lpVtbl->SetPipelineState1(This,pStateObject))
#undef ID3D12GraphicsCommandList7_DispatchRays
#define ID3D12GraphicsCommandList7_DispatchRays(This,pDesc) (dzn_trace_note((This), "DispatchRays"), (This)->lpVtbl->DispatchRays(This,pDesc))
#undef ID3D12GraphicsCommandList7_RSSetShadingRate
#define ID3D12GraphicsCommandList7_RSSetShadingRate(This,baseShadingRate,combiners) (dzn_trace_note((This), "RSSetShadingRate"), (This)->lpVtbl->RSSetShadingRate(This,baseShadingRate,combiners))
#undef ID3D12GraphicsCommandList7_RSSetShadingRateImage
#define ID3D12GraphicsCommandList7_RSSetShadingRateImage(This,shadingRateImage) (dzn_trace_note((This), "RSSetShadingRateImage"), (This)->lpVtbl->RSSetShadingRateImage(This,shadingRateImage))
#undef ID3D12GraphicsCommandList7_DispatchMesh
#define ID3D12GraphicsCommandList7_DispatchMesh(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "DispatchMesh"), (This)->lpVtbl->DispatchMesh(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList7_Barrier
#define ID3D12GraphicsCommandList7_Barrier(This,NumBarrierGroups,pBarrierGroups) (dzn_trace_note((This), "Barrier"), (This)->lpVtbl->Barrier(This,NumBarrierGroups,pBarrierGroups))
#undef ID3D12GraphicsCommandList8_Close
#define ID3D12GraphicsCommandList8_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList8_Reset
#define ID3D12GraphicsCommandList8_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList8_ClearState
#define ID3D12GraphicsCommandList8_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList8_DrawInstanced
#define ID3D12GraphicsCommandList8_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList8_DrawIndexedInstanced
#define ID3D12GraphicsCommandList8_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList8_Dispatch
#define ID3D12GraphicsCommandList8_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList8_CopyBufferRegion
#define ID3D12GraphicsCommandList8_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList8_CopyTextureRegion
#define ID3D12GraphicsCommandList8_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList8_CopyResource
#define ID3D12GraphicsCommandList8_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList8_CopyTiles
#define ID3D12GraphicsCommandList8_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList8_ResolveSubresource
#define ID3D12GraphicsCommandList8_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList8_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList8_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList8_RSSetViewports
#define ID3D12GraphicsCommandList8_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList8_RSSetScissorRects
#define ID3D12GraphicsCommandList8_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList8_OMSetBlendFactor
#define ID3D12GraphicsCommandList8_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList8_OMSetStencilRef
#define ID3D12GraphicsCommandList8_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList8_SetPipelineState
#define ID3D12GraphicsCommandList8_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList8_ResourceBarrier
#define ID3D12GraphicsCommandList8_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList8_ExecuteBundle
#define ID3D12GraphicsCommandList8_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList8_SetDescriptorHeaps
#define ID3D12GraphicsCommandList8_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList8_SetComputeRootSignature
#define ID3D12GraphicsCommandList8_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList8_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList8_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList8_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList8_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList8_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList8_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList8_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList8_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList8_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList8_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList8_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList8_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList8_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList8_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList8_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList8_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList8_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList8_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList8_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList8_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList8_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList8_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList8_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList8_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList8_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList8_IASetIndexBuffer
#define ID3D12GraphicsCommandList8_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList8_IASetVertexBuffers
#define ID3D12GraphicsCommandList8_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList8_SOSetTargets
#define ID3D12GraphicsCommandList8_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList8_OMSetRenderTargets
#define ID3D12GraphicsCommandList8_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList8_ClearDepthStencilView
#define ID3D12GraphicsCommandList8_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList8_ClearRenderTargetView
#define ID3D12GraphicsCommandList8_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList8_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList8_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList8_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList8_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList8_DiscardResource
#define ID3D12GraphicsCommandList8_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList8_BeginQuery
#define ID3D12GraphicsCommandList8_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList8_EndQuery
#define ID3D12GraphicsCommandList8_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList8_ResolveQueryData
#define ID3D12GraphicsCommandList8_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList8_SetPredication
#define ID3D12GraphicsCommandList8_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList8_SetMarker
#define ID3D12GraphicsCommandList8_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList8_BeginEvent
#define ID3D12GraphicsCommandList8_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList8_EndEvent
#define ID3D12GraphicsCommandList8_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList8_ExecuteIndirect
#define ID3D12GraphicsCommandList8_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList8_AtomicCopyBufferUINT
#define ID3D12GraphicsCommandList8_AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT"), (This)->lpVtbl->AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList8_AtomicCopyBufferUINT64
#define ID3D12GraphicsCommandList8_AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT64"), (This)->lpVtbl->AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList8_OMSetDepthBounds
#define ID3D12GraphicsCommandList8_OMSetDepthBounds(This,Min,Max) (dzn_trace_note((This), "OMSetDepthBounds"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList8 *)dzn_probe_list_)->lpVtbl->OMSetDepthBounds(((ID3D12GraphicsCommandList8 *)dzn_probe_list_),Min,Max), dzn_probe_end("OMSetDepthBounds") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetDepthBounds(This,Min,Max))
#undef ID3D12GraphicsCommandList8_SetSamplePositions
#define ID3D12GraphicsCommandList8_SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions) (dzn_trace_note((This), "SetSamplePositions"), (This)->lpVtbl->SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions))
#undef ID3D12GraphicsCommandList8_ResolveSubresourceRegion
#define ID3D12GraphicsCommandList8_ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode) (dzn_trace_note((This), "ResolveSubresourceRegion"), (This)->lpVtbl->ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode))
#undef ID3D12GraphicsCommandList8_SetViewInstanceMask
#define ID3D12GraphicsCommandList8_SetViewInstanceMask(This,Mask) (dzn_trace_note((This), "SetViewInstanceMask"), (This)->lpVtbl->SetViewInstanceMask(This,Mask))
#undef ID3D12GraphicsCommandList8_WriteBufferImmediate
#define ID3D12GraphicsCommandList8_WriteBufferImmediate(This,Count,pParams,pModes) (dzn_trace_note((This), "WriteBufferImmediate"), (This)->lpVtbl->WriteBufferImmediate(This,Count,pParams,pModes))
#undef ID3D12GraphicsCommandList8_SetProtectedResourceSession
#define ID3D12GraphicsCommandList8_SetProtectedResourceSession(This,pProtectedResourceSession) (dzn_trace_note((This), "SetProtectedResourceSession"), (This)->lpVtbl->SetProtectedResourceSession(This,pProtectedResourceSession))
#undef ID3D12GraphicsCommandList8_BeginRenderPass
#define ID3D12GraphicsCommandList8_BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags) (dzn_trace_note((This), "BeginRenderPass"), (This)->lpVtbl->BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags))
#undef ID3D12GraphicsCommandList8_EndRenderPass
#define ID3D12GraphicsCommandList8_EndRenderPass(This) (dzn_trace_note((This), "EndRenderPass"), (This)->lpVtbl->EndRenderPass(This))
#undef ID3D12GraphicsCommandList8_InitializeMetaCommand
#define ID3D12GraphicsCommandList8_InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes) (dzn_trace_note((This), "InitializeMetaCommand"), (This)->lpVtbl->InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList8_ExecuteMetaCommand
#define ID3D12GraphicsCommandList8_ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes) (dzn_trace_note((This), "ExecuteMetaCommand"), (This)->lpVtbl->ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList8_BuildRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList8_BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs) (dzn_trace_note((This), "BuildRaytracingAccelerationStructure"), (This)->lpVtbl->BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs))
#undef ID3D12GraphicsCommandList8_EmitRaytracingAccelerationStructurePostbuildInfo
#define ID3D12GraphicsCommandList8_EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData) (dzn_trace_note((This), "EmitRaytracingAccelerationStructurePostbuildInfo"), (This)->lpVtbl->EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData))
#undef ID3D12GraphicsCommandList8_CopyRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList8_CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode) (dzn_trace_note((This), "CopyRaytracingAccelerationStructure"), (This)->lpVtbl->CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode))
#undef ID3D12GraphicsCommandList8_SetPipelineState1
#define ID3D12GraphicsCommandList8_SetPipelineState1(This,pStateObject) (dzn_trace_note((This), "SetPipelineState1"), (This)->lpVtbl->SetPipelineState1(This,pStateObject))
#undef ID3D12GraphicsCommandList8_DispatchRays
#define ID3D12GraphicsCommandList8_DispatchRays(This,pDesc) (dzn_trace_note((This), "DispatchRays"), (This)->lpVtbl->DispatchRays(This,pDesc))
#undef ID3D12GraphicsCommandList8_RSSetShadingRate
#define ID3D12GraphicsCommandList8_RSSetShadingRate(This,baseShadingRate,combiners) (dzn_trace_note((This), "RSSetShadingRate"), (This)->lpVtbl->RSSetShadingRate(This,baseShadingRate,combiners))
#undef ID3D12GraphicsCommandList8_RSSetShadingRateImage
#define ID3D12GraphicsCommandList8_RSSetShadingRateImage(This,shadingRateImage) (dzn_trace_note((This), "RSSetShadingRateImage"), (This)->lpVtbl->RSSetShadingRateImage(This,shadingRateImage))
#undef ID3D12GraphicsCommandList8_DispatchMesh
#define ID3D12GraphicsCommandList8_DispatchMesh(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "DispatchMesh"), (This)->lpVtbl->DispatchMesh(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList8_Barrier
#define ID3D12GraphicsCommandList8_Barrier(This,NumBarrierGroups,pBarrierGroups) (dzn_trace_note((This), "Barrier"), (This)->lpVtbl->Barrier(This,NumBarrierGroups,pBarrierGroups))
#undef ID3D12GraphicsCommandList8_OMSetFrontAndBackStencilRef
#define ID3D12GraphicsCommandList8_OMSetFrontAndBackStencilRef(This,FrontStencilRef,BackStencilRef) (dzn_trace_note((This), "OMSetFrontAndBackStencilRef"), (This)->lpVtbl->OMSetFrontAndBackStencilRef(This,FrontStencilRef,BackStencilRef))
#undef ID3D12GraphicsCommandList9_Close
#define ID3D12GraphicsCommandList9_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList9_Reset
#define ID3D12GraphicsCommandList9_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList9_ClearState
#define ID3D12GraphicsCommandList9_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList9_DrawInstanced
#define ID3D12GraphicsCommandList9_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList9_DrawIndexedInstanced
#define ID3D12GraphicsCommandList9_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList9_Dispatch
#define ID3D12GraphicsCommandList9_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList9_CopyBufferRegion
#define ID3D12GraphicsCommandList9_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList9_CopyTextureRegion
#define ID3D12GraphicsCommandList9_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList9_CopyResource
#define ID3D12GraphicsCommandList9_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList9_CopyTiles
#define ID3D12GraphicsCommandList9_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList9_ResolveSubresource
#define ID3D12GraphicsCommandList9_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList9_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList9_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList9_RSSetViewports
#define ID3D12GraphicsCommandList9_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList9_RSSetScissorRects
#define ID3D12GraphicsCommandList9_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList9_OMSetBlendFactor
#define ID3D12GraphicsCommandList9_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList9_OMSetStencilRef
#define ID3D12GraphicsCommandList9_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList9_SetPipelineState
#define ID3D12GraphicsCommandList9_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList9_ResourceBarrier
#define ID3D12GraphicsCommandList9_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList9_ExecuteBundle
#define ID3D12GraphicsCommandList9_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList9_SetDescriptorHeaps
#define ID3D12GraphicsCommandList9_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList9_SetComputeRootSignature
#define ID3D12GraphicsCommandList9_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList9_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList9_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList9_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList9_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList9_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList9_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList9_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList9_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList9_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList9_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList9_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList9_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList9_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList9_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList9_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList9_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList9_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList9_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList9_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList9_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList9_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList9_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList9_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList9_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList9_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList9_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList9_IASetIndexBuffer
#define ID3D12GraphicsCommandList9_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList9_IASetVertexBuffers
#define ID3D12GraphicsCommandList9_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList9_SOSetTargets
#define ID3D12GraphicsCommandList9_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList9_OMSetRenderTargets
#define ID3D12GraphicsCommandList9_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList9_ClearDepthStencilView
#define ID3D12GraphicsCommandList9_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList9_ClearRenderTargetView
#define ID3D12GraphicsCommandList9_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList9_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList9_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList9_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList9_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList9_DiscardResource
#define ID3D12GraphicsCommandList9_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList9_BeginQuery
#define ID3D12GraphicsCommandList9_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList9_EndQuery
#define ID3D12GraphicsCommandList9_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList9_ResolveQueryData
#define ID3D12GraphicsCommandList9_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList9_SetPredication
#define ID3D12GraphicsCommandList9_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList9_SetMarker
#define ID3D12GraphicsCommandList9_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList9_BeginEvent
#define ID3D12GraphicsCommandList9_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList9_EndEvent
#define ID3D12GraphicsCommandList9_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList9_ExecuteIndirect
#define ID3D12GraphicsCommandList9_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList9_AtomicCopyBufferUINT
#define ID3D12GraphicsCommandList9_AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT"), (This)->lpVtbl->AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList9_AtomicCopyBufferUINT64
#define ID3D12GraphicsCommandList9_AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT64"), (This)->lpVtbl->AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList9_OMSetDepthBounds
#define ID3D12GraphicsCommandList9_OMSetDepthBounds(This,Min,Max) (dzn_trace_note((This), "OMSetDepthBounds"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList9 *)dzn_probe_list_)->lpVtbl->OMSetDepthBounds(((ID3D12GraphicsCommandList9 *)dzn_probe_list_),Min,Max), dzn_probe_end("OMSetDepthBounds") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetDepthBounds(This,Min,Max))
#undef ID3D12GraphicsCommandList9_SetSamplePositions
#define ID3D12GraphicsCommandList9_SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions) (dzn_trace_note((This), "SetSamplePositions"), (This)->lpVtbl->SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions))
#undef ID3D12GraphicsCommandList9_ResolveSubresourceRegion
#define ID3D12GraphicsCommandList9_ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode) (dzn_trace_note((This), "ResolveSubresourceRegion"), (This)->lpVtbl->ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode))
#undef ID3D12GraphicsCommandList9_SetViewInstanceMask
#define ID3D12GraphicsCommandList9_SetViewInstanceMask(This,Mask) (dzn_trace_note((This), "SetViewInstanceMask"), (This)->lpVtbl->SetViewInstanceMask(This,Mask))
#undef ID3D12GraphicsCommandList9_WriteBufferImmediate
#define ID3D12GraphicsCommandList9_WriteBufferImmediate(This,Count,pParams,pModes) (dzn_trace_note((This), "WriteBufferImmediate"), (This)->lpVtbl->WriteBufferImmediate(This,Count,pParams,pModes))
#undef ID3D12GraphicsCommandList9_SetProtectedResourceSession
#define ID3D12GraphicsCommandList9_SetProtectedResourceSession(This,pProtectedResourceSession) (dzn_trace_note((This), "SetProtectedResourceSession"), (This)->lpVtbl->SetProtectedResourceSession(This,pProtectedResourceSession))
#undef ID3D12GraphicsCommandList9_BeginRenderPass
#define ID3D12GraphicsCommandList9_BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags) (dzn_trace_note((This), "BeginRenderPass"), (This)->lpVtbl->BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags))
#undef ID3D12GraphicsCommandList9_EndRenderPass
#define ID3D12GraphicsCommandList9_EndRenderPass(This) (dzn_trace_note((This), "EndRenderPass"), (This)->lpVtbl->EndRenderPass(This))
#undef ID3D12GraphicsCommandList9_InitializeMetaCommand
#define ID3D12GraphicsCommandList9_InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes) (dzn_trace_note((This), "InitializeMetaCommand"), (This)->lpVtbl->InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList9_ExecuteMetaCommand
#define ID3D12GraphicsCommandList9_ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes) (dzn_trace_note((This), "ExecuteMetaCommand"), (This)->lpVtbl->ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList9_BuildRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList9_BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs) (dzn_trace_note((This), "BuildRaytracingAccelerationStructure"), (This)->lpVtbl->BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs))
#undef ID3D12GraphicsCommandList9_EmitRaytracingAccelerationStructurePostbuildInfo
#define ID3D12GraphicsCommandList9_EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData) (dzn_trace_note((This), "EmitRaytracingAccelerationStructurePostbuildInfo"), (This)->lpVtbl->EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData))
#undef ID3D12GraphicsCommandList9_CopyRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList9_CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode) (dzn_trace_note((This), "CopyRaytracingAccelerationStructure"), (This)->lpVtbl->CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode))
#undef ID3D12GraphicsCommandList9_SetPipelineState1
#define ID3D12GraphicsCommandList9_SetPipelineState1(This,pStateObject) (dzn_trace_note((This), "SetPipelineState1"), (This)->lpVtbl->SetPipelineState1(This,pStateObject))
#undef ID3D12GraphicsCommandList9_DispatchRays
#define ID3D12GraphicsCommandList9_DispatchRays(This,pDesc) (dzn_trace_note((This), "DispatchRays"), (This)->lpVtbl->DispatchRays(This,pDesc))
#undef ID3D12GraphicsCommandList9_RSSetShadingRate
#define ID3D12GraphicsCommandList9_RSSetShadingRate(This,baseShadingRate,combiners) (dzn_trace_note((This), "RSSetShadingRate"), (This)->lpVtbl->RSSetShadingRate(This,baseShadingRate,combiners))
#undef ID3D12GraphicsCommandList9_RSSetShadingRateImage
#define ID3D12GraphicsCommandList9_RSSetShadingRateImage(This,shadingRateImage) (dzn_trace_note((This), "RSSetShadingRateImage"), (This)->lpVtbl->RSSetShadingRateImage(This,shadingRateImage))
#undef ID3D12GraphicsCommandList9_DispatchMesh
#define ID3D12GraphicsCommandList9_DispatchMesh(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "DispatchMesh"), (This)->lpVtbl->DispatchMesh(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList9_Barrier
#define ID3D12GraphicsCommandList9_Barrier(This,NumBarrierGroups,pBarrierGroups) (dzn_trace_note((This), "Barrier"), (This)->lpVtbl->Barrier(This,NumBarrierGroups,pBarrierGroups))
#undef ID3D12GraphicsCommandList9_OMSetFrontAndBackStencilRef
#define ID3D12GraphicsCommandList9_OMSetFrontAndBackStencilRef(This,FrontStencilRef,BackStencilRef) (dzn_trace_note((This), "OMSetFrontAndBackStencilRef"), (This)->lpVtbl->OMSetFrontAndBackStencilRef(This,FrontStencilRef,BackStencilRef))
#undef ID3D12GraphicsCommandList9_RSSetDepthBias
#define ID3D12GraphicsCommandList9_RSSetDepthBias(This,DepthBias,DepthBiasClamp,SlopeScaledDepthBias) (dzn_trace_note((This), "RSSetDepthBias"), (This)->lpVtbl->RSSetDepthBias(This,DepthBias,DepthBiasClamp,SlopeScaledDepthBias))
#undef ID3D12GraphicsCommandList9_IASetIndexBufferStripCutValue
#define ID3D12GraphicsCommandList9_IASetIndexBufferStripCutValue(This,IBStripCutValue) (dzn_trace_note((This), "IASetIndexBufferStripCutValue"), (This)->lpVtbl->IASetIndexBufferStripCutValue(This,IBStripCutValue))
#undef ID3D12GraphicsCommandList10_Close
#define ID3D12GraphicsCommandList10_Close(This) (dzn_trace_note((This), "Close"), (This)->lpVtbl->Close(This))
#undef ID3D12GraphicsCommandList10_Reset
#define ID3D12GraphicsCommandList10_Reset(This,pAllocator,pInitialState) (dzn_trace_note((This), "Reset"), (This)->lpVtbl->Reset(This,pAllocator,pInitialState))
#undef ID3D12GraphicsCommandList10_ClearState
#define ID3D12GraphicsCommandList10_ClearState(This,pPipelineState) (dzn_trace_note((This), "ClearState"), (This)->lpVtbl->ClearState(This,pPipelineState))
#undef ID3D12GraphicsCommandList10_DrawInstanced
#define ID3D12GraphicsCommandList10_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawInstanced"), (This)->lpVtbl->DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList10_DrawIndexedInstanced
#define ID3D12GraphicsCommandList10_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) (dzn_trace_note((This), "DrawIndexedInstanced"), (This)->lpVtbl->DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation))
#undef ID3D12GraphicsCommandList10_Dispatch
#define ID3D12GraphicsCommandList10_Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "Dispatch"), (This)->lpVtbl->Dispatch(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList10_CopyBufferRegion
#define ID3D12GraphicsCommandList10_CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes) (dzn_trace_note((This), "CopyBufferRegion"), dzn_trace_copy_buf((This),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->CopyBufferRegion(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes), dzn_probe_end("CopyBufferRegion") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyBufferRegion(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,NumBytes))
#undef ID3D12GraphicsCommandList10_CopyTextureRegion
#define ID3D12GraphicsCommandList10_CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox) (dzn_trace_note((This), "CopyTextureRegion"), dzn_trace_copy_tex((This),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->CopyTextureRegion(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),pDst,DstX,DstY,DstZ,pSrc,pSrcBox), dzn_probe_end("CopyTextureRegion") ? (dzn_probe_detail_CopyTextureRegion(pDst,DstX,DstY,DstZ,pSrc,pSrcBox), 0) : 0) : 0), (This)->lpVtbl->CopyTextureRegion(This,pDst,DstX,DstY,DstZ,pSrc,pSrcBox))
#undef ID3D12GraphicsCommandList10_CopyResource
#define ID3D12GraphicsCommandList10_CopyResource(This,pDstResource,pSrcResource) (dzn_trace_note((This), "CopyResource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->CopyResource(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),pDstResource,pSrcResource), dzn_probe_end("CopyResource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->CopyResource(This,pDstResource,pSrcResource))
#undef ID3D12GraphicsCommandList10_CopyTiles
#define ID3D12GraphicsCommandList10_CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags) (dzn_trace_note((This), "CopyTiles"), (This)->lpVtbl->CopyTiles(This,pTiledResource,pTileRegionStartCoordinate,pTileRegionSize,pBuffer,BufferStartOffsetInBytes,Flags))
#undef ID3D12GraphicsCommandList10_ResolveSubresource
#define ID3D12GraphicsCommandList10_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) (dzn_trace_note((This), "ResolveSubresource"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->ResolveSubresource(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format), dzn_probe_end("ResolveSubresource") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format))
#undef ID3D12GraphicsCommandList10_IASetPrimitiveTopology
#define ID3D12GraphicsCommandList10_IASetPrimitiveTopology(This,PrimitiveTopology) (dzn_trace_note((This), "IASetPrimitiveTopology"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->IASetPrimitiveTopology(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),PrimitiveTopology), dzn_probe_end("IASetPrimitiveTopology") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetPrimitiveTopology(This,PrimitiveTopology))
#undef ID3D12GraphicsCommandList10_RSSetViewports
#define ID3D12GraphicsCommandList10_RSSetViewports(This,NumViewports,pViewports) (dzn_trace_note((This), "RSSetViewports"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->RSSetViewports(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),NumViewports,pViewports), dzn_probe_end("RSSetViewports") ? (dzn_probe_detail_RSSetViewports(NumViewports,pViewports), 0) : 0) : 0), (This)->lpVtbl->RSSetViewports(This,NumViewports,pViewports))
#undef ID3D12GraphicsCommandList10_RSSetScissorRects
#define ID3D12GraphicsCommandList10_RSSetScissorRects(This,NumRects,pRects) (dzn_trace_note((This), "RSSetScissorRects"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->RSSetScissorRects(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),NumRects,pRects), dzn_probe_end("RSSetScissorRects") ? (dzn_probe_detail_RSSetScissorRects(NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->RSSetScissorRects(This,NumRects,pRects))
#undef ID3D12GraphicsCommandList10_OMSetBlendFactor
#define ID3D12GraphicsCommandList10_OMSetBlendFactor(This,BlendFactor) (dzn_trace_note((This), "OMSetBlendFactor"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->OMSetBlendFactor(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),BlendFactor), dzn_probe_end("OMSetBlendFactor") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetBlendFactor(This,BlendFactor))
#undef ID3D12GraphicsCommandList10_OMSetStencilRef
#define ID3D12GraphicsCommandList10_OMSetStencilRef(This,StencilRef) (dzn_trace_note((This), "OMSetStencilRef"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->OMSetStencilRef(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),StencilRef), dzn_probe_end("OMSetStencilRef") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetStencilRef(This,StencilRef))
#undef ID3D12GraphicsCommandList10_SetPipelineState
#define ID3D12GraphicsCommandList10_SetPipelineState(This,pPipelineState) (dzn_trace_note((This), "SetPipelineState"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->SetPipelineState(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),pPipelineState), dzn_probe_end("SetPipelineState") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetPipelineState(This,pPipelineState))
#undef ID3D12GraphicsCommandList10_ResourceBarrier
#define ID3D12GraphicsCommandList10_ResourceBarrier(This,NumBarriers,pBarriers) (dzn_trace_note((This), "ResourceBarrier"), dzn_trace_check_barriers((This),NumBarriers,pBarriers), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->ResourceBarrier(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),NumBarriers,pBarriers), dzn_probe_end("ResourceBarrier") ? (dzn_probe_detail_ResourceBarrier(NumBarriers,pBarriers), 0) : 0) : 0), (This)->lpVtbl->ResourceBarrier(This,NumBarriers,pBarriers))
#undef ID3D12GraphicsCommandList10_ExecuteBundle
#define ID3D12GraphicsCommandList10_ExecuteBundle(This,pCommandList) (dzn_trace_note((This), "ExecuteBundle"), (This)->lpVtbl->ExecuteBundle(This,pCommandList))
#undef ID3D12GraphicsCommandList10_SetDescriptorHeaps
#define ID3D12GraphicsCommandList10_SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps) (dzn_trace_note((This), "SetDescriptorHeaps"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->SetDescriptorHeaps(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),NumDescriptorHeaps,ppDescriptorHeaps), dzn_probe_end("SetDescriptorHeaps") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetDescriptorHeaps(This,NumDescriptorHeaps,ppDescriptorHeaps))
#undef ID3D12GraphicsCommandList10_SetComputeRootSignature
#define ID3D12GraphicsCommandList10_SetComputeRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetComputeRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->SetComputeRootSignature(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetComputeRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetComputeRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList10_SetGraphicsRootSignature
#define ID3D12GraphicsCommandList10_SetGraphicsRootSignature(This,pRootSignature) (dzn_trace_note((This), "SetGraphicsRootSignature"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->SetGraphicsRootSignature(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),pRootSignature), dzn_probe_end("SetGraphicsRootSignature") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->SetGraphicsRootSignature(This,pRootSignature))
#undef ID3D12GraphicsCommandList10_SetComputeRootDescriptorTable
#define ID3D12GraphicsCommandList10_SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetComputeRootDescriptorTable"), (This)->lpVtbl->SetComputeRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList10_SetGraphicsRootDescriptorTable
#define ID3D12GraphicsCommandList10_SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor) (dzn_trace_note((This), "SetGraphicsRootDescriptorTable"), (This)->lpVtbl->SetGraphicsRootDescriptorTable(This,RootParameterIndex,BaseDescriptor))
#undef ID3D12GraphicsCommandList10_SetComputeRoot32BitConstant
#define ID3D12GraphicsCommandList10_SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstant"), (This)->lpVtbl->SetComputeRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList10_SetGraphicsRoot32BitConstant
#define ID3D12GraphicsCommandList10_SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstant"), (This)->lpVtbl->SetGraphicsRoot32BitConstant(This,RootParameterIndex,SrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList10_SetComputeRoot32BitConstants
#define ID3D12GraphicsCommandList10_SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetComputeRoot32BitConstants"), (This)->lpVtbl->SetComputeRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList10_SetGraphicsRoot32BitConstants
#define ID3D12GraphicsCommandList10_SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues) (dzn_trace_note((This), "SetGraphicsRoot32BitConstants"), (This)->lpVtbl->SetGraphicsRoot32BitConstants(This,RootParameterIndex,Num32BitValuesToSet,pSrcData,DestOffsetIn32BitValues))
#undef ID3D12GraphicsCommandList10_SetComputeRootConstantBufferView
#define ID3D12GraphicsCommandList10_SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootConstantBufferView"), (This)->lpVtbl->SetComputeRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList10_SetGraphicsRootConstantBufferView
#define ID3D12GraphicsCommandList10_SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootConstantBufferView"), (This)->lpVtbl->SetGraphicsRootConstantBufferView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList10_SetComputeRootShaderResourceView
#define ID3D12GraphicsCommandList10_SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootShaderResourceView"), (This)->lpVtbl->SetComputeRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList10_SetGraphicsRootShaderResourceView
#define ID3D12GraphicsCommandList10_SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootShaderResourceView"), (This)->lpVtbl->SetGraphicsRootShaderResourceView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList10_SetComputeRootUnorderedAccessView
#define ID3D12GraphicsCommandList10_SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetComputeRootUnorderedAccessView"), (This)->lpVtbl->SetComputeRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList10_SetGraphicsRootUnorderedAccessView
#define ID3D12GraphicsCommandList10_SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation) (dzn_trace_note((This), "SetGraphicsRootUnorderedAccessView"), (This)->lpVtbl->SetGraphicsRootUnorderedAccessView(This,RootParameterIndex,BufferLocation))
#undef ID3D12GraphicsCommandList10_IASetIndexBuffer
#define ID3D12GraphicsCommandList10_IASetIndexBuffer(This,pView) (dzn_trace_note((This), "IASetIndexBuffer"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->IASetIndexBuffer(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),pView), dzn_probe_end("IASetIndexBuffer") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->IASetIndexBuffer(This,pView))
#undef ID3D12GraphicsCommandList10_IASetVertexBuffers
#define ID3D12GraphicsCommandList10_IASetVertexBuffers(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "IASetVertexBuffers"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->IASetVertexBuffers(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),StartSlot,NumViews,pViews), dzn_probe_end("IASetVertexBuffers") ? (dzn_probe_detail_IASetVertexBuffers(StartSlot,NumViews,pViews), 0) : 0) : 0), (This)->lpVtbl->IASetVertexBuffers(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList10_SOSetTargets
#define ID3D12GraphicsCommandList10_SOSetTargets(This,StartSlot,NumViews,pViews) (dzn_trace_note((This), "SOSetTargets"), (This)->lpVtbl->SOSetTargets(This,StartSlot,NumViews,pViews))
#undef ID3D12GraphicsCommandList10_OMSetRenderTargets
#define ID3D12GraphicsCommandList10_OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor) (dzn_trace_note((This), "OMSetRenderTargets"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->OMSetRenderTargets(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), dzn_probe_end("OMSetRenderTargets") ? (dzn_probe_detail_OMSetRenderTargets(NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor), 0) : 0) : 0), (This)->lpVtbl->OMSetRenderTargets(This,NumRenderTargetDescriptors,pRenderTargetDescriptors,RTsSingleHandleToDescriptorRange,pDepthStencilDescriptor))
#undef ID3D12GraphicsCommandList10_ClearDepthStencilView
#define ID3D12GraphicsCommandList10_ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects) (dzn_trace_note((This), "ClearDepthStencilView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->ClearDepthStencilView(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects), dzn_probe_end("ClearDepthStencilView") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearDepthStencilView(This,DepthStencilView,ClearFlags,Depth,Stencil,NumRects,pRects))
#undef ID3D12GraphicsCommandList10_ClearRenderTargetView
#define ID3D12GraphicsCommandList10_ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects) (dzn_trace_note((This), "ClearRenderTargetView"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->ClearRenderTargetView(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),RenderTargetView,ColorRGBA,NumRects,pRects), dzn_probe_end("ClearRenderTargetView") ? (dzn_probe_detail_ClearRenderTargetView(RenderTargetView,ColorRGBA,NumRects,pRects), 0) : 0) : 0), (This)->lpVtbl->ClearRenderTargetView(This,RenderTargetView,ColorRGBA,NumRects,pRects))
#undef ID3D12GraphicsCommandList10_ClearUnorderedAccessViewUint
#define ID3D12GraphicsCommandList10_ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewUint"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewUint(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewUint") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewUint(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList10_ClearUnorderedAccessViewFloat
#define ID3D12GraphicsCommandList10_ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects) (dzn_trace_note((This), "ClearUnorderedAccessViewFloat"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->ClearUnorderedAccessViewFloat(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects), dzn_probe_end("ClearUnorderedAccessViewFloat") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->ClearUnorderedAccessViewFloat(This,ViewGPUHandleInCurrentHeap,ViewCPUHandle,pResource,Values,NumRects,pRects))
#undef ID3D12GraphicsCommandList10_DiscardResource
#define ID3D12GraphicsCommandList10_DiscardResource(This,pResource,pRegion) (dzn_trace_note((This), "DiscardResource"), (This)->lpVtbl->DiscardResource(This,pResource,pRegion))
#undef ID3D12GraphicsCommandList10_BeginQuery
#define ID3D12GraphicsCommandList10_BeginQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "BeginQuery"), (This)->lpVtbl->BeginQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList10_EndQuery
#define ID3D12GraphicsCommandList10_EndQuery(This,pQueryHeap,Type,Index) (dzn_trace_note((This), "EndQuery"), (This)->lpVtbl->EndQuery(This,pQueryHeap,Type,Index))
#undef ID3D12GraphicsCommandList10_ResolveQueryData
#define ID3D12GraphicsCommandList10_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) (dzn_trace_note((This), "ResolveQueryData"), (This)->lpVtbl->ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset))
#undef ID3D12GraphicsCommandList10_SetPredication
#define ID3D12GraphicsCommandList10_SetPredication(This,pBuffer,AlignedBufferOffset,Operation) (dzn_trace_note((This), "SetPredication"), (This)->lpVtbl->SetPredication(This,pBuffer,AlignedBufferOffset,Operation))
#undef ID3D12GraphicsCommandList10_SetMarker
#define ID3D12GraphicsCommandList10_SetMarker(This,Metadata,pData,Size) (dzn_trace_note((This), "SetMarker"), (This)->lpVtbl->SetMarker(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList10_BeginEvent
#define ID3D12GraphicsCommandList10_BeginEvent(This,Metadata,pData,Size) (dzn_trace_note((This), "BeginEvent"), (This)->lpVtbl->BeginEvent(This,Metadata,pData,Size))
#undef ID3D12GraphicsCommandList10_EndEvent
#define ID3D12GraphicsCommandList10_EndEvent(This) (dzn_trace_note((This), "EndEvent"), (This)->lpVtbl->EndEvent(This))
#undef ID3D12GraphicsCommandList10_ExecuteIndirect
#define ID3D12GraphicsCommandList10_ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset) (dzn_trace_note((This), "ExecuteIndirect"), (This)->lpVtbl->ExecuteIndirect(This,pCommandSignature,MaxCommandCount,pArgumentBuffer,ArgumentBufferOffset,pCountBuffer,CountBufferOffset))
#undef ID3D12GraphicsCommandList10_AtomicCopyBufferUINT
#define ID3D12GraphicsCommandList10_AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT"), (This)->lpVtbl->AtomicCopyBufferUINT(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList10_AtomicCopyBufferUINT64
#define ID3D12GraphicsCommandList10_AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges) (dzn_trace_note((This), "AtomicCopyBufferUINT64"), (This)->lpVtbl->AtomicCopyBufferUINT64(This,pDstBuffer,DstOffset,pSrcBuffer,SrcOffset,Dependencies,ppDependentResources,pDependentSubresourceRanges))
#undef ID3D12GraphicsCommandList10_OMSetDepthBounds
#define ID3D12GraphicsCommandList10_OMSetDepthBounds(This,Min,Max) (dzn_trace_note((This), "OMSetDepthBounds"), (void)((dzn_probe_list_ = dzn_probe_begin(This)) ? (((ID3D12GraphicsCommandList10 *)dzn_probe_list_)->lpVtbl->OMSetDepthBounds(((ID3D12GraphicsCommandList10 *)dzn_probe_list_),Min,Max), dzn_probe_end("OMSetDepthBounds") ? ((void)0, 0) : 0) : 0), (This)->lpVtbl->OMSetDepthBounds(This,Min,Max))
#undef ID3D12GraphicsCommandList10_SetSamplePositions
#define ID3D12GraphicsCommandList10_SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions) (dzn_trace_note((This), "SetSamplePositions"), (This)->lpVtbl->SetSamplePositions(This,NumSamplesPerPixel,NumPixels,pSamplePositions))
#undef ID3D12GraphicsCommandList10_ResolveSubresourceRegion
#define ID3D12GraphicsCommandList10_ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode) (dzn_trace_note((This), "ResolveSubresourceRegion"), (This)->lpVtbl->ResolveSubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,pSrcResource,SrcSubresource,pSrcRect,Format,ResolveMode))
#undef ID3D12GraphicsCommandList10_SetViewInstanceMask
#define ID3D12GraphicsCommandList10_SetViewInstanceMask(This,Mask) (dzn_trace_note((This), "SetViewInstanceMask"), (This)->lpVtbl->SetViewInstanceMask(This,Mask))
#undef ID3D12GraphicsCommandList10_WriteBufferImmediate
#define ID3D12GraphicsCommandList10_WriteBufferImmediate(This,Count,pParams,pModes) (dzn_trace_note((This), "WriteBufferImmediate"), (This)->lpVtbl->WriteBufferImmediate(This,Count,pParams,pModes))
#undef ID3D12GraphicsCommandList10_SetProtectedResourceSession
#define ID3D12GraphicsCommandList10_SetProtectedResourceSession(This,pProtectedResourceSession) (dzn_trace_note((This), "SetProtectedResourceSession"), (This)->lpVtbl->SetProtectedResourceSession(This,pProtectedResourceSession))
#undef ID3D12GraphicsCommandList10_BeginRenderPass
#define ID3D12GraphicsCommandList10_BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags) (dzn_trace_note((This), "BeginRenderPass"), (This)->lpVtbl->BeginRenderPass(This,NumRenderTargets,pRenderTargets,pDepthStencil,Flags))
#undef ID3D12GraphicsCommandList10_EndRenderPass
#define ID3D12GraphicsCommandList10_EndRenderPass(This) (dzn_trace_note((This), "EndRenderPass"), (This)->lpVtbl->EndRenderPass(This))
#undef ID3D12GraphicsCommandList10_InitializeMetaCommand
#define ID3D12GraphicsCommandList10_InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes) (dzn_trace_note((This), "InitializeMetaCommand"), (This)->lpVtbl->InitializeMetaCommand(This,pMetaCommand,pInitializationParametersData,InitializationParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList10_ExecuteMetaCommand
#define ID3D12GraphicsCommandList10_ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes) (dzn_trace_note((This), "ExecuteMetaCommand"), (This)->lpVtbl->ExecuteMetaCommand(This,pMetaCommand,pExecutionParametersData,ExecutionParametersDataSizeInBytes))
#undef ID3D12GraphicsCommandList10_BuildRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList10_BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs) (dzn_trace_note((This), "BuildRaytracingAccelerationStructure"), (This)->lpVtbl->BuildRaytracingAccelerationStructure(This,pDesc,NumPostbuildInfoDescs,pPostbuildInfoDescs))
#undef ID3D12GraphicsCommandList10_EmitRaytracingAccelerationStructurePostbuildInfo
#define ID3D12GraphicsCommandList10_EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData) (dzn_trace_note((This), "EmitRaytracingAccelerationStructurePostbuildInfo"), (This)->lpVtbl->EmitRaytracingAccelerationStructurePostbuildInfo(This,pDesc,NumSourceAccelerationStructures,pSourceAccelerationStructureData))
#undef ID3D12GraphicsCommandList10_CopyRaytracingAccelerationStructure
#define ID3D12GraphicsCommandList10_CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode) (dzn_trace_note((This), "CopyRaytracingAccelerationStructure"), (This)->lpVtbl->CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode))
#undef ID3D12GraphicsCommandList10_SetPipelineState1
#define ID3D12GraphicsCommandList10_SetPipelineState1(This,pStateObject) (dzn_trace_note((This), "SetPipelineState1"), (This)->lpVtbl->SetPipelineState1(This,pStateObject))
#undef ID3D12GraphicsCommandList10_DispatchRays
#define ID3D12GraphicsCommandList10_DispatchRays(This,pDesc) (dzn_trace_note((This), "DispatchRays"), (This)->lpVtbl->DispatchRays(This,pDesc))
#undef ID3D12GraphicsCommandList10_RSSetShadingRate
#define ID3D12GraphicsCommandList10_RSSetShadingRate(This,baseShadingRate,combiners) (dzn_trace_note((This), "RSSetShadingRate"), (This)->lpVtbl->RSSetShadingRate(This,baseShadingRate,combiners))
#undef ID3D12GraphicsCommandList10_RSSetShadingRateImage
#define ID3D12GraphicsCommandList10_RSSetShadingRateImage(This,shadingRateImage) (dzn_trace_note((This), "RSSetShadingRateImage"), (This)->lpVtbl->RSSetShadingRateImage(This,shadingRateImage))
#undef ID3D12GraphicsCommandList10_DispatchMesh
#define ID3D12GraphicsCommandList10_DispatchMesh(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ) (dzn_trace_note((This), "DispatchMesh"), (This)->lpVtbl->DispatchMesh(This,ThreadGroupCountX,ThreadGroupCountY,ThreadGroupCountZ))
#undef ID3D12GraphicsCommandList10_Barrier
#define ID3D12GraphicsCommandList10_Barrier(This,NumBarrierGroups,pBarrierGroups) (dzn_trace_note((This), "Barrier"), (This)->lpVtbl->Barrier(This,NumBarrierGroups,pBarrierGroups))
#undef ID3D12GraphicsCommandList10_OMSetFrontAndBackStencilRef
#define ID3D12GraphicsCommandList10_OMSetFrontAndBackStencilRef(This,FrontStencilRef,BackStencilRef) (dzn_trace_note((This), "OMSetFrontAndBackStencilRef"), (This)->lpVtbl->OMSetFrontAndBackStencilRef(This,FrontStencilRef,BackStencilRef))
#undef ID3D12GraphicsCommandList10_RSSetDepthBias
#define ID3D12GraphicsCommandList10_RSSetDepthBias(This,DepthBias,DepthBiasClamp,SlopeScaledDepthBias) (dzn_trace_note((This), "RSSetDepthBias"), (This)->lpVtbl->RSSetDepthBias(This,DepthBias,DepthBiasClamp,SlopeScaledDepthBias))
#undef ID3D12GraphicsCommandList10_IASetIndexBufferStripCutValue
#define ID3D12GraphicsCommandList10_IASetIndexBufferStripCutValue(This,IBStripCutValue) (dzn_trace_note((This), "IASetIndexBufferStripCutValue"), (This)->lpVtbl->IASetIndexBufferStripCutValue(This,IBStripCutValue))
#undef ID3D12GraphicsCommandList10_SetProgram
#define ID3D12GraphicsCommandList10_SetProgram(This,pDesc) (dzn_trace_note((This), "SetProgram"), (This)->lpVtbl->SetProgram(This,pDesc))
#undef ID3D12GraphicsCommandList10_DispatchGraph
#define ID3D12GraphicsCommandList10_DispatchGraph(This,pDesc) (dzn_trace_note((This), "DispatchGraph"), (This)->lpVtbl->DispatchGraph(This,pDesc))
#endif
