#pragma once

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
			int crc;
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
			int crc;
		};

		struct SRGBChunk
		{
			Chunk chunk;
			char mode;
			int crc;
		};

		struct PLTEChunk
		{
		};

		struct IDATChunk
		{
			Chunk chunk;
			char* data;
			int crc;
		};

		struct IENDChunk
		{
			Chunk chunk;
			int crc;
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

	struct TextureData
	{
		int width;
		int height;
		char* data;
	};
}
