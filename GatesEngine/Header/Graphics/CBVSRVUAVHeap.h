#pragma once
#include "GraphicsDevice.h"

namespace GatesEngine
{
	class CBVSRVUAVHeap
	{
	private:
		GraphicsDevice* graphicsDevice;
		ID3D12DescriptorHeap* heap;
		Math::Vector3 useCount;
		bool isCreated;
	public:
		~CBVSRVUAVHeap();
		void SetGraphicsDevice(GraphicsDevice* pGraphicsDevice);
		void Create(const Math::Vector3& useCount);
		ID3D12DescriptorHeap* GetHeap();
		Math::Vector3 GetUseCount();
	};
}
