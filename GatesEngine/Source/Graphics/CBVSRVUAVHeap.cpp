#include "..\..\Header\Graphics\CBVSRVUAVHeap.h"
#include "..\..\Header\Graphics\COMRelease.h"

GatesEngine::CBVSRVUAVHeap::~CBVSRVUAVHeap()
{
	COM_RELEASE(heap);
}

void GatesEngine::CBVSRVUAVHeap::SetGraphicsDevice(GraphicsDevice* pGraphicsDevice)
{
	graphicsDevice = pGraphicsDevice;
}

void GatesEngine::CBVSRVUAVHeap::Create(const Math::Vector3& useCount)
{
	if (isCreated)return;
	if (!graphicsDevice)return;

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.NodeMask = 0;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.NumDescriptors = (int)useCount.x + (int)useCount.y + (int)useCount.z;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	HRESULT result = graphicsDevice->GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap));

	this->useCount = useCount;
}

ID3D12DescriptorHeap* GatesEngine::CBVSRVUAVHeap::GetHeap()
{
	return heap;
}

GatesEngine::Math::Vector3 GatesEngine::CBVSRVUAVHeap::GetUseCount()
{
	return useCount;
}
