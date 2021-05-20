#pragma once
#include <vector>
#include <d3d12.h>
namespace GatesEngine
{
	class GraphicsDevice;
	class RenderTarget
	{
	protected:
		GraphicsDevice* pGraphicsDevice;
		ID3D12DescriptorHeap* rtvHeap;
		std::vector<ID3D12Resource*> pResources;
	public:
		RenderTarget();
		virtual ~RenderTarget();
		ID3D12DescriptorHeap* GetHeap();
		bool Create(GraphicsDevice* wrapper, std::vector<ID3D12Resource*>* resources);
		bool Create(GraphicsDevice* wrapper, ID3D12Resource* resource);
		virtual void Prepare() {};
	};
}