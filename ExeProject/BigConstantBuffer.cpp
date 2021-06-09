#include "BigConstantBuffer.h"
#include "Header/Graphics/COMRelease.h"

BigConstantBuffer::~BigConstantBuffer()
{
	buffer->Unmap(0, {});
	COM_RELEASE(buffer);
}

void BigConstantBuffer::SetGraphicsDevice(GatesEngine::GraphicsDevice* pGraphicsDevice)
{
	graphicsDevice = pGraphicsDevice;
}

void BigConstantBuffer::CreateBuffer()
{
	//生成済みorデバイスがセットされていないなら即リターン
	if (isCreated)return;
	if (!graphicsDevice)return;
	if (!heap)return;

	//定数バッファの設定
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resDesc.Width = ((1 + 0xff) & ~0xff) * (int)heap->GetUseCount().x;
	HRESULT result = graphicsDevice->GetDevice()->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&buffer));

	buffer->Map(0, {}, (void**)&mappedConstantBuffer);

	isCreated = true;
}

void BigConstantBuffer::SetHeap(CBV_SRV_UAV_Heap* pHeap)
{
	heap = pHeap;
}

void BigConstantBuffer::ResetCurrentUseNumber()
{
	currentBufferNumber = 0;
}

void BigConstantBuffer::BindAndAttachData(int desIndex, const void* data, int size)
{
	if (!heap)return;

	//データを巨大なバッファにセット
	int aizeAligned = (size + 0xff) & ~0xff;
	int numRequired = aizeAligned / 0x100;

	if (currentBufferNumber + numRequired > (int)heap->GetUseCount().x)return;

	int top = currentBufferNumber;

	memcpy(mappedConstantBuffer + top, data, size);

	//CBVを生成
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
	cbvDesc.BufferLocation = buffer->GetGPUVirtualAddress() + top * 0x100;
	cbvDesc.SizeInBytes = aizeAligned;

	D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetHeap()->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += graphicsDevice->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * currentBufferNumber;
	graphicsDevice->GetDevice()->CreateConstantBufferView(&cbvDesc, handle);

	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = heap->GetHeap()->GetGPUDescriptorHandleForHeapStart();
	gpuHandle.ptr += graphicsDevice->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * currentBufferNumber;

	ID3D12DescriptorHeap* ppHeaps[] = { heap->GetHeap() };
	graphicsDevice->GetCmdList()->SetDescriptorHeaps(1, ppHeaps);

	graphicsDevice->GetCmdList()->SetGraphicsRootDescriptorTable(desIndex, gpuHandle);

	currentBufferNumber += numRequired;
}
