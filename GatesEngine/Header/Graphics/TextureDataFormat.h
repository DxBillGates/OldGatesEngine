#pragma once
#include <vector>

namespace GatesEngine
{
	struct PNGFormatData
	{
		struct PNGSignature
		{
			char signature[8];
		};

		struct Chunk
		{
			unsigned long chunkDataSize;
			char chunkType[4];
		};

		struct IHDRChunk
		{
			Chunk chunk;
			unsigned long width;
			unsigned long height;
			char bitDepth;
			char colorType;
			char compression;
			char filter;
			char interlace;
			unsigned long crc;
		};

		struct GAMAChunk
		{
			Chunk chunk;
			int gammaValue;
			int crc;
		};

		struct CHRMChunk
		{
			Chunk chunk;
			int whitePointX;
			int whitePointY;
			int redX;
			int redY;
			int greenX;
			int greenY;
			int blueX;
			int blueY;
			unsigned long crc;
		};

		struct SRGBChunk
		{
			Chunk chunk;
			char mode;
			unsigned long crc;
		};

		struct PLTEChunk
		{
		};

		struct IDATChunk
		{
			Chunk chunk;
			char* data;
			unsigned long crc;
		};

		struct IENDChunk
		{
			Chunk chunk;
			unsigned long crc;
		};

		PNGSignature signature;
		IHDRChunk iHDRChunk;
		GAMAChunk gammaChunk;
		CHRMChunk cHRMChunk;
		SRGBChunk sRGBChunk;
		PLTEChunk platteChunk;
		IDATChunk dataChunk;
		IENDChunk endChunk;
	};

	struct ColorData
	{
		char b, g, r, a;
	};

	struct BMPFormatData
	{
		struct BMPFileHeader
		{
			struct BMPFileHeaderData
			{
				unsigned long dataSize;
				unsigned short reserved1;
				unsigned short reserved2;
				unsigned long offset;
			};
			char type[2];
			BMPFileHeaderData data;
		};

		struct BMPInfoHeader
		{
			unsigned long biSize;
			unsigned long biWidth;
			unsigned long biHeight;
			unsigned short biPlanes;
			unsigned short biBitCount;
			unsigned long biCompression;
			unsigned long biSizeImage;
			unsigned long biXPixPerMeter;
			unsigned long biYPixPerMeter;
			unsigned long biClrUsed;
			unsigned long biCirImportant;
		};


		BMPFileHeader fileHeader;
		BMPInfoHeader infoHeader;
		std::vector<ColorData> data;
	};

	struct TextureData
	{
		int width;
		int height;
		void* data;
	};
}
