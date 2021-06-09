#pragma once
#include "..\..\Graphics\Mesh.h"
#include <map>
#include <string>

namespace GatesEngine
{
	class MeshManager
	{
	private:
		GraphicsDevice* graphicsDevice;
		std::map<std::string, Mesh*> meshes;
	public:
		MeshManager(GraphicsDevice* pGraphicsDevice);
		~MeshManager();
		Mesh* Add(const std::string& name);
		Mesh* GetMesh(const std::string& name);
	};
}
