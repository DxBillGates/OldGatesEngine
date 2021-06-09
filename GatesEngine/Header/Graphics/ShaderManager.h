#pragma once
#include "Shader.h"
#include <map>
#include <string>

namespace GatesEngine
{
	class ShaderManager
	{
	private:
		std::map<std::string, Shader*> shaders;
	public:
		Shader* Add(Shader* addShader, const std::string& name);
		Shader* GetShader(const std::string& name);
	};
}
