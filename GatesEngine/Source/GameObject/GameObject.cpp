#include "..\..\Header\GameObject\GameObject.h"
#include "..\..\Header\Component\Component.h"
#include "..\..\Header\Component\Behaviour.h"
#include "..\..\Header\GameObject\GameObjectManager.h"
#include "..\..\Header\Scene\Scene.h"
#include "..\..\Header\Application\Application.h"

GatesEngine::GameObject::GameObject():GameObject("none","none")
{
}

GatesEngine::GameObject::GameObject(const char* name, const char* tag) : name(name), tag(tag), manager(nullptr),transform(Math::Transform())
{
}

GatesEngine::GameObject::~GameObject()
{
	for (auto itr = components.begin(); itr != components.end(); ++itr)
	{
		delete (*itr);
	}
	for (auto itr = behaviors.begin(); itr != behaviors.end(); ++itr)
	{
		delete (*itr);
	}
	components.clear();
	behaviors.clear();
}

void GatesEngine::GameObject::Start()
{
	for (auto itr = components.begin(); itr != components.end(); ++itr)
	{
		(*itr)->Start();
	}
	for (auto itr = behaviors.begin(); itr != behaviors.end(); ++itr)
	{
		(*itr)->Start();
	}
}

void GatesEngine::GameObject::Update()
{
	for (auto itr = components.begin(); itr != components.end(); ++itr)
	{
		(*itr)->Update();
	}
	for (auto itr = behaviors.begin(); itr != behaviors.end(); ++itr)
	{
		(*itr)->Update();
	}
}

GatesEngine::Math::Transform& GatesEngine::GameObject::GetTransform()
{
	return transform;
}

void GatesEngine::GameObject::SetManager(GameObjectManager* manager)
{
	this->manager = manager;
}

GatesEngine::GameObjectManager* GatesEngine::GameObject::GetManager()
{
	return manager;
}
