#include "..\..\Header\Graphics\Texture.h"
#include "..\..\Header\Graphics\Graphics.h"
#include "..\..\..\DirectXTex\DirectXTex.h"
#include "..\..\Header\Graphics\COMRelease.h"

GatesEngine::Texture::Texture()
	: tGraphicsDevice(nullptr)
	, texBuff(nullptr)
	, srvNumber(0)
{
}

GatesEngine::Texture::~Texture()
{
	COM_RELEASE(texBuff);
}

void GatesEngine::Texture::Load(GraphicsDevice* graphicsDevice, const std::string& filename)
{
	tGraphicsDevice = graphicsDevice;
	std::string filepath = "Resources/Texture/" + filename;
	wchar_t wFilepath[128];
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, filepath.c_str(), -1, wFilepath, _countof(wFilepath));
	
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImage;
	const DirectX::Image* image;

	DirectX::LoadFromWICFile(wFilepath, DirectX::WIC_FLAGS_NONE, &metadata, scratchImage);
	image = scratchImage.GetImage(0, 0, 0);
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = static_cast<D3D12_RESOURCE_DIMENSION>(metadata.dimension);
	resDesc.Format = metadata.format;
	resDesc.Width = (UINT64)metadata.width;
	resDesc.Height = (UINT)metadata.height;
	resDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	resDesc.MipLevels = (UINT16)metadata.mipLevels;
	resDesc.SampleDesc.Count = 1;

	graphicsDevice->GetDevice()->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&texBuff));
	texBuff->WriteToSubresource(0, nullptr, image->pixels, (UINT)image->rowPitch, (UINT)image->slicePitch);
	srvNumber = graphicsDevice->GetCBVSRVUAVHeap()->GetNextSrvNumber();
	graphicsDevice->GetCBVSRVUAVHeap()->CreateSRV(texBuff);
}

void GatesEngine::Texture::Set(int descIndex)
{
	tGraphicsDevice->GetCmdList()->SetGraphicsRootDescriptorTable(descIndex, tGraphicsDevice->GetCBVSRVUAVHeap()->GetSRVHandleForSRV(srvNumber));
}
