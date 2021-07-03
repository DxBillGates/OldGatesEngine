#pragma once
#include <fstream>
#include <sstream>
#include <string>

namespace GatesEngine
{
	class FileLoader
	{
	public:
		static bool Skip(std::string target, std::ifstream& file);
		static void Skip(int byte, std::ifstream& file);
		static uint32_t Swap32bit(uint32_t value);
	};
}
