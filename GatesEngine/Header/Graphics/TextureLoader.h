#pragma once
#include "TextureDataFormat.h"
#include "..\Util\FileLoader.h"

namespace GatesEngine
{
	class TextureLoader
	{
	private:
		static PNGFormatData* backupPNGFormatData;
		static BMPFormatData* backupBMPFormatData;
		static TextureData* currentLoadTextureData;
	public:
		static TextureData* LoadPngTextureData(const std::string& filename);
		static TextureData* LoadBmpTextureData(const std::string& filename);
		static void DeleteData();
	};
}
