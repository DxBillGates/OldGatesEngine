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
