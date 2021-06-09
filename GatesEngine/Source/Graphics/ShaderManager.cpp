#include "..\..\Header\Graphics\ShaderManager.h"
#include <cassert>

GatesEngine::Shader* GatesEngine::ShaderManager::Add(Shader* addShader, const std::string& name)
{
	shaders.insert(std::make_pair(name.c_str(), addShader));
	return addShader;
}

GatesEngine::Shader* GatesEngine::ShaderManager::GetShader(const std::string& name)
{
	Shader* shader = shaders.at(name);
	if (!shader)
	{
		printf("%sShader‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ\n", name.c_str());
		assert(-1);
	}
	return shader;
}
