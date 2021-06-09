#include "CBV_SRV_UAV_Heap.h"
#include "Header/Graphics/COMRelease.h"

CBV_SRV_UAV_Heap::~CBV_SRV_UAV_Heap()
{
	COM_RELEASE(heap);
}

void CBV_SRV_UAV_Heap::SetGraphicsDevice(GatesEngine::GraphicsDevice* pGraphicsDevice)
{
	graphicsDevice = pGraphicsDevice;
}

void CBV_SRV_UAV_Heap::Create(const GatesEngine::Math::Vector3& useCount)
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

ID3D12DescriptorHeap* CBV_SRV_UAV_Heap::GetHeap()
{
	return heap;
}

GatesEngine::Math::Vector3 CBV_SRV_UAV_Heap::GetUseCount()
{
	return useCount;
}
