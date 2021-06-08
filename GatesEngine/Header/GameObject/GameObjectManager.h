#pragma once
#include "GameObject.h"
namespace GatesEngine
{
	class Scene;
	class GameObjectManager
	{
	private:
		std::vector<GameObject*> gameObjects;
		Scene* scene;
	public:
		GameObjectManager();
		~GameObjectManager();
		GameObject* Add(GameObject* newGameObject);
		void SetScene(Scene* setScene);
		Scene* GetScene();
		void Start();
		void Update();
	};
}
