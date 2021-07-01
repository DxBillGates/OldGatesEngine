#pragma once
#include "GraphicsDevice.h"
#include "TextureDataFormat.h"

namespace GatesEngine
{
	class Texture
	{
	private:
		GraphicsDevice* pgraphicsDevice;
		ID3D12Resource* texBuffer;
		int srvNum;
	public:
		Texture();
		Texture(TextureData* data,GraphicsDevice* pGraphicsDevice);
		virtual ~Texture();
		virtual void Set(int descIndex);
	};
}