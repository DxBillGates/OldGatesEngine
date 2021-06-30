#pragma once
#include "TextureDataFormat.h"
#include "..\Util\FileLoader.h"

namespace GatesEngine
{
	class TextureLoader
	{
	private:
		static PNGFormatData* backupPNGFormatData;
		static TextureData* currentLoadTextureData;
	public:
		static TextureData* LoadPngTextureData(const std::string& filename);
	};
}
