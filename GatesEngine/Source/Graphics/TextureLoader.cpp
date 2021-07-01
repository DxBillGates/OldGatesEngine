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

	//IHDRまでスキップ(IHDRチャンクの構造体はアライメントが起きるので1個ずつ読み込む)
	if (FileLoader::Skip("IHDR", file))
	{
		//IHDR識別バイナリの前に4バイト分データサイズがあるから現在位置から4バイト分戻る
		FileLoader::Skip(-4, file);

		//チャンクのデータサイズと識別バイナリを読み込む(8byte)
		file.read((char*)&backupPNGFormatData->iHDRChunk.chunk, sizeof(PNGFormatData::IHDRChunk::chunk));

		//画像サイズを読み込む
		file.read((char*)&backupPNGFormatData->iHDRChunk.width, sizeof(PNGFormatData::IHDRChunk::width));
		file.read((char*)&backupPNGFormatData->iHDRChunk.height, sizeof(PNGFormatData::IHDRChunk::height));

		//ビット深度を読み込む
		file.read((char*)&backupPNGFormatData->iHDRChunk.bitDepth, sizeof(char));

		//圧縮手法、フィルター手法、インターレース手法を読み込む
		file.read((char*)&backupPNGFormatData->iHDRChunk.compression, sizeof(char));
		file.read((char*)&backupPNGFormatData->iHDRChunk.filter, sizeof(char));
		file.read((char*)&backupPNGFormatData->iHDRChunk.interlace, sizeof(char));

		//CRC読み込み
		file.read((char*)&backupPNGFormatData->iHDRChunk.crc, sizeof(PNGFormatData::IHDRChunk::crc));
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
