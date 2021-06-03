#pragma once
#include "Component.h"
#include "..\Graphics\Mesh.h"
namespace GatesEngine
{
	class MeshComponent : public Component
	{
	private:
		Mesh* pMesh;
	public:
		MeshComponent();
		Mesh* GetMesh();
		void SetMesh(Mesh* pMesh);
	};
}
