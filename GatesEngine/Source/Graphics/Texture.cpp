#include "..\..\Header\Graphics\Texture.h"
#include "..\..\Header\Graphics\Graphics.h"
#include "..\..\Header\Graphics\COMRelease.h"

GatesEngine::Texture::Texture()
	:pgraphicsDevice(nullptr)
	, texBuffer(nullptr)
	, srvNum(0)
{
}

GatesEngine::Texture::Texture(TextureData* data, GraphicsDevice* pGraphicsDevice)
	:pgraphicsDevice(pGraphicsDevice)
	,texBuffer(nullptr)
	,srvNum(0)
{
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	resDesc.Width = (UINT64)data->width;
	resDesc.Height = (UINT64)data->height;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	pgraphicsDevice->GetDevice()->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&texBuffer));
	texBuffer->WriteToSubresource(0, nullptr, data->data, (UINT64)data->width * 4, (UINT64)data->width * data->height * 4);

	srvNum = pgraphicsDevice->GetCBVSRVUAVHeap()->GetNextSrvNumber();
	pgraphicsDevice->GetCBVSRVUAVHeap()->CreateSRV(texBuffer);
}

GatesEngine::Texture::~Texture()
{
	COM_RELEASE(texBuffer);
}

void GatesEngine::Texture::Set(int descIndex)
{
	pgraphicsDevice->GetCmdList()->SetGraphicsRootDescriptorTable(descIndex, pgraphicsDevice->GetCBVSRVUAVHeap()->GetSRVHandleForSRV(srvNum));
}
