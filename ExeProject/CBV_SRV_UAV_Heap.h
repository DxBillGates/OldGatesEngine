#pragma once
#include "Header/Math/Math.h"
#include "Header/Graphics/GraphicsDevice.h"
class CBV_SRV_UAV_Heap
{
private:
	GatesEngine::GraphicsDevice* graphicsDevice;
	ID3D12DescriptorHeap* heap;
	GatesEngine::Math::Vector3 useCount;
	bool isCreated;
public:
	~CBV_SRV_UAV_Heap();
	void SetGraphicsDevice(GatesEngine::GraphicsDevice* pGraphicsDevice);
	void Create(const GatesEngine::Math::Vector3& useCount);
	ID3D12DescriptorHeap* GetHeap();
	GatesEngine::Math::Vector3 GetUseCount();
};

