#include "..\..\Header\GameObject\GameObjectManager.h"

GatesEngine::GameObjectManager::GameObjectManager():scene(nullptr)
{
}

GatesEngine::GameObjectManager::~GameObjectManager()
{
	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
	{
		delete (*itr);
	}
}

GatesEngine::GameObject* GatesEngine::GameObjectManager::Add(GameObject* newGameObject)
{
	gameObjects.push_back(newGameObject);
	newGameObject->SetManager(this);
	return newGameObject;
}

void GatesEngine::GameObjectManager::SetScene(Scene* setScene)
{
	scene = setScene;
}

GatesEngine::Scene* GatesEngine::GameObjectManager::GetScene()
{
	return scene;
}

void GatesEngine::GameObjectManager::Start()
{
	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
	{
		(*itr)->Start();
	}
}

void GatesEngine::GameObjectManager::Update()
{
	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
	{
		(*itr)->Update();
	}
}
