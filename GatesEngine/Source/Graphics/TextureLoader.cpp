#include "..\..\Header\Graphics\TextureLoader.h"
#include <assert.h>

GatesEngine::PNGFormatData* GatesEngine::TextureLoader::backupPNGFormatData = nullptr;
GatesEngine::TextureData* GatesEngine::TextureLoader::currentLoadTextureData = nullptr;

GatesEngine::TextureData* GatesEngine::TextureLoader::LoadPngTextureData(const std::string& filename)
{
	if (currentLoadTextureData)delete currentLoadTextureData;
	else currentLoadTextureData = new TextureData();
	
	if (backupPNGFormatData)delete backupPNGFormatData;
	else backupPNGFormatData = new PNGFormatData();

	using namespace std;
	ifstream file;
	file.open(filename, ios_base::binary);
	if (file.fail())assert(0);

	file.read((char*)&backupPNGFormatData->signature, sizeof(PNGFormatData::PNGSignature));
	file.read((char*)&backupPNGFormatData->iHDRChunk, sizeof(PNGFormatData::IHDRChunk)-3);
	if (FileLoader::Skip("IEND", file))
	{
		FileLoader::Skip(-4, file);
		file.read((char*)&backupPNGFormatData->endChunk, sizeof(PNGFormatData::IENDChunk));
	}

	return currentLoadTextureData;
}
