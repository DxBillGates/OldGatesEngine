#include "..\..\Header\Util\FileLoader.h"

bool GatesEngine::FileLoader::Skip(std::string target, std::ifstream& file)
{
	auto currentPos = file.tellg();
	std::string s = "";
	int i = 0;
	while (s != target && !file.eof())
	{
		char read;
		file.read((char*)&read, sizeof(read));
		if (read == target[i])
		{
			++i;
			s += read;
		}
		else
		{
			i = 0;
			s = "";
		}
	}

	if (s == target)
	{
		int size = (int)target.size();
		Skip(-(size), file);
		return true;
	}
	else
	{
		file.seekg(((int)currentPos), std::ios_base::beg);
		return false;
	}
	return false;
}

void GatesEngine::FileLoader::Skip(int byte, std::ifstream& file)
{
	auto currentPos = file.tellg();
	file.seekg((((int)currentPos) + byte), std::ios_base::beg);
}

uint32_t GatesEngine::FileLoader::Swap32bit(uint32_t value)
{
	uint32_t result;
	result = value << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= value >> 24;
	return result;
}