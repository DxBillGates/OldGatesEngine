#pragma once
#include "CBV_SRV_UAV_Heap.h"
class BigConstantBuffer
{
private:
	GatesEngine::GraphicsDevice* graphicsDevice;
	CBV_SRV_UAV_Heap* heap;
	ID3D12Resource* buffer;
	struct { char buf[256]; } *mappedConstantBuffer;
	int currentBufferNumber;
	bool isCreated;
public:
	~BigConstantBuffer();
	void SetGraphicsDevice(GatesEngine::GraphicsDevice* pGraphicsDevice);
	void SetHeap(CBV_SRV_UAV_Heap* pHeap);
	void CreateBuffer();
	void ResetCurrentUseNumber();
	void BindAndAttachData(int desIndex, const void* data, int size);
};

