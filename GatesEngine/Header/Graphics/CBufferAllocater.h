#pragma once
#include "GraphicsDevice.h"
#include "CBVSRVUAVHeap.h"

namespace GatesEngine
{
	class CBufferAllocater
	{
	private:
		GraphicsDevice* graphicsDevice;
		CBVSRVUAVHeap* heap;
		ID3D12Resource* buffer;
		struct { char buf[256]; }*mappedBuffer;
		int currentUseNumber;
		bool isCreated;
	public:
		~CBufferAllocater();
		void SetGraphicsDevice(GraphicsDevice* pGraphicsDevice);
		void SetHeap(CBVSRVUAVHeap* pHeap);
		void Create();
		void ResetCurrentUseNumber();
		void BindAndAttachData(int descIndex, const void* data, int size);
	};
}