#include "..\..\Header\Component\MeshComponent.h"
#include "..\..\Header\GameObject\GameObject.h"

GatesEngine::MeshComponent::MeshComponent()
	:pMesh(nullptr)
{
}

GatesEngine::Mesh* GatesEngine::MeshComponent::GetMesh()
{
	return pMesh;
}

void GatesEngine::MeshComponent::SetMesh(Mesh* pMesh)
{
	gameObject->SetMeshComponent(this);
	this->pMesh = pMesh;
}
