#include "..\..\Header\Graphics\TextureLoader.h"
#include <assert.h>

GatesEngine::PNGFormatData* GatesEngine::TextureLoader::backupPNGFormatData = nullptr;
GatesEngine::BMPFormatData* GatesEngine::TextureLoader::backupBMPFormatData = nullptr;
GatesEngine::TextureData* GatesEngine::TextureLoader::currentLoadTextureData = nullptr;

GatesEngine::TextureData* GatesEngine::TextureLoader::LoadPngTextureData(const std::string& filename)
{
	//�o�b�N�A�b�v�f�[�^�̔j�����������m��
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

	//PNG�V�O�l�`����ǂݍ���
	file.read((char*)&backupPNGFormatData->signature, sizeof(PNGFormatData::PNGSignature));

	//IHDR�܂ŃX�L�b�v(IHDR�`�����N�̍\���̂̓A���C�����g���N����̂�1���ǂݍ���)
	if (FileLoader::Skip("IHDR", file))
	{
		//IHDR���ʃo�C�i���̑O��4�o�C�g���f�[�^�T�C�Y�����邩�猻�݈ʒu����4�o�C�g���߂�
		FileLoader::Skip(-4, file);

		//�`�����N�̃f�[�^�T�C�Y�Ǝ��ʃo�C�i����ǂݍ���(8byte)
		file.read((char*)&backupPNGFormatData->iHDRChunk.chunk, sizeof(PNGFormatData::IHDRChunk::chunk));

		//�摜�T�C�Y��ǂݍ���
		file.read((char*)&backupPNGFormatData->iHDRChunk.width, sizeof(PNGFormatData::IHDRChunk::width));
		file.read((char*)&backupPNGFormatData->iHDRChunk.height, sizeof(PNGFormatData::IHDRChunk::height));

		//�r�b�g�[�x��ǂݍ���
		file.read((char*)&backupPNGFormatData->iHDRChunk.bitDepth, sizeof(char));

		//���k��@�A�t�B���^�[��@�A�C���^�[���[�X��@��ǂݍ���
		file.read((char*)&backupPNGFormatData->iHDRChunk.compression, sizeof(char));
		file.read((char*)&backupPNGFormatData->iHDRChunk.filter, sizeof(char));
		file.read((char*)&backupPNGFormatData->iHDRChunk.interlace, sizeof(char));

		//CRC�ǂݍ���
		file.read((char*)&backupPNGFormatData->iHDRChunk.crc, sizeof(PNGFormatData::IHDRChunk::crc));
	}

	//IEND�`�����N���ʃo�C�i���܂Ŕ���4�o�C�g�߂���IEND�`�����N��ǂݍ���
	if (FileLoader::Skip("IEND", file))
	{
		FileLoader::Skip(-4, file);
		file.read((char*)&backupPNGFormatData->endChunk, sizeof(PNGFormatData::IENDChunk));
	}

	return currentLoadTextureData;
}

GatesEngine::TextureData* GatesEngine::TextureLoader::LoadBmpTextureData(const std::string& filename)
{
	//�o�b�N�A�b�v�f�[�^�̔j�����������m��
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

	//�t�@�C���w�b�_�̓A���C�����g���N����̂ō\���̂�2��`���ēǂݍ���
	file.read((char*)&backupBMPFormatData->fileHeader.type, sizeof(BMPFormatData::BMPFileHeader::type));
	file.read((char*)&backupBMPFormatData->fileHeader.data, sizeof(BMPFormatData::BMPFileHeader::data));

	//�t�@�C���C���t�H�ǂݍ���
	file.read((char*)&backupBMPFormatData->infoHeader, sizeof(BMPFormatData::BMPInfoHeader));

	//�摜�f�[�^�ǂݍ���
	backupBMPFormatData->data.resize((uint64_t)backupBMPFormatData->infoHeader.biWidth * backupBMPFormatData->infoHeader.biHeight);
	file.read((char*)backupBMPFormatData->data.data(), backupBMPFormatData->data.size()*4);

	//�摜�f�[�^�A�������^�[��
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
