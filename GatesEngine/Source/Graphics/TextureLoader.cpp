#include "..\..\Header\Graphics\TextureLoader.h"
#include <assert.h>

GatesEngine::PNGFormatData* GatesEngine::TextureLoader::backupPNGFormatData = nullptr;
GatesEngine::BMPFormatData* GatesEngine::TextureLoader::backupBMPFormatData = nullptr;
GatesEngine::TextureData* GatesEngine::TextureLoader::currentLoadTextureData = nullptr;

GatesEngine::TextureData* GatesEngine::TextureLoader::LoadPngTextureData(const std::string& filename)
{
	//バックアップデータの破棄＆メモリ確保
	if (currentLoadTextureData)
	{
		delete currentLoadTextureData;
		currentLoadTextureData = new TextureData();
	}
	else currentLoadTextureData = new TextureData();
	
	if (backupPNGFormatData)
	{
		delete backupPNGFormatData;
		backupPNGFormatData = new PNGFormatData();
	}
	else backupPNGFormatData = new PNGFormatData();

	using namespace std;
	ifstream file;
	file.open(filename, ios_base::binary);
	if (file.fail())assert(0);

	//PNGシグネチャを読み込む
	file.read((char*)&backupPNGFormatData->signature, sizeof(PNGFormatData::PNGSignature));
	//IHDRチャンク読込
	file.read((char*)&backupPNGFormatData->iHDRChunk, sizeof(PNGFormatData::IHDRChunk)-3);
	//エンディアン変換
	backupPNGFormatData->iHDRChunk.chunk.chunkDataSize = FileLoader::Swap32bit(backupPNGFormatData->iHDRChunk.chunk.chunkDataSize);
	backupPNGFormatData->iHDRChunk.width = FileLoader::Swap32bit(backupPNGFormatData->iHDRChunk.width);
	backupPNGFormatData->iHDRChunk.height = FileLoader::Swap32bit(backupPNGFormatData->iHDRChunk.height);

	//IDATチャンク読込
	if (FileLoader::Skip("IDAT", file))
	{
		FileLoader::Skip(-4, file);
		file.read((char*)&backupPNGFormatData->dataChunk.chunk, sizeof(PNGFormatData::Chunk));
		backupPNGFormatData->dataChunk.chunk.chunkDataSize = FileLoader::Swap32bit(backupPNGFormatData->dataChunk.chunk.chunkDataSize);
		std::vector<unsigned char> data(backupPNGFormatData->dataChunk.chunk.chunkDataSize);
		file.read((char*)data.data(), backupPNGFormatData->dataChunk.chunk.chunkDataSize);
		file.read((char*)&backupPNGFormatData->dataChunk.crc, sizeof(uint32_t));
		backupPNGFormatData->dataChunk.crc = FileLoader::Swap32bit(backupPNGFormatData->dataChunk.crc);
	}

	//IENDチャンク識別バイナリまで飛んで4バイト戻ってIENDチャンクを読み込む
	if (FileLoader::Skip("IEND", file))
	{
		FileLoader::Skip(-4, file);
		file.read((char*)&backupPNGFormatData->endChunk, sizeof(PNGFormatData::IENDChunk));
	}

	return currentLoadTextureData;
}

GatesEngine::TextureData* GatesEngine::TextureLoader::LoadBmpTextureData(const std::string& filename)
{
	//バックアップデータの破棄＆メモリ確保
	if (currentLoadTextureData)
	{
		delete currentLoadTextureData;
		currentLoadTextureData = new TextureData();
	}
	else currentLoadTextureData = new TextureData();

	if (backupBMPFormatData)
	{
		delete backupBMPFormatData;
		backupBMPFormatData = new BMPFormatData();
	}
	else backupBMPFormatData = new BMPFormatData();

	using namespace std;
	ifstream file;
	file.open(filename, ios_base::binary);
	if (file.fail())assert(0);

	//ファイルヘッダはアライメントが起きるので構造体を2つ定義して読み込む
	file.read((char*)&backupBMPFormatData->fileHeader.type, sizeof(BMPFormatData::BMPFileHeader::type));
	file.read((char*)&backupBMPFormatData->fileHeader.data, sizeof(BMPFormatData::BMPFileHeader::data));

	//ファイルインフォ読み込み
	file.read((char*)&backupBMPFormatData->infoHeader, sizeof(BMPFormatData::BMPInfoHeader));

	//画像データ読み込み
	backupBMPFormatData->data.resize((uint64_t)backupBMPFormatData->infoHeader.biWidth * backupBMPFormatData->infoHeader.biHeight);
	file.read((char*)backupBMPFormatData->data.data(), backupBMPFormatData->data.size()*4);

	//画像データ、情報をリターン
	currentLoadTextureData->width = backupBMPFormatData->infoHeader.biWidth;
	currentLoadTextureData->height = backupBMPFormatData->infoHeader.biHeight;
	currentLoadTextureData->data = backupBMPFormatData->data.data();

	return currentLoadTextureData;
}

void GatesEngine::TextureLoader::DeleteData()
{
	delete backupBMPFormatData;
	delete backupPNGFormatData;
	delete currentLoadTextureData;
}
