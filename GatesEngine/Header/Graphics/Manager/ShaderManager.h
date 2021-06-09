#pragma once
#include "..\..\Graphics\Shader.h"
#include <map>
#include <string>

namespace GatesEngine
{
	class ShaderManager
	{
	private:
		GraphicsDevice* graphicsDevice;
		std::map<std::string, Shader*> shaders;
	public:
		ShaderManager(GraphicsDevice* pGraphicsDevice);
		~ShaderManager();
		Shader* Add(Shader* addShader, const std::string& name);
		Shader* GetShader(const std::string& name);
	};
}
