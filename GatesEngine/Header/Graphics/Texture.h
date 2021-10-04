#pragma once
#include "GraphicsDevice.h"
#include <string>

namespace GatesEngine
{
	class Texture
	{
	private:
		GraphicsDevice* tGraphicsDevice;
	protected:
		ID3D12Resource* texBuff;
		int srvNumber;
	public:
		Texture();
		virtual ~Texture();
		void Load(GraphicsDevice* graphicsDevice, const std::string& filename);
		virtual void Set(int descIndex);
	};
}