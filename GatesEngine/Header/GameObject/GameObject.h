#pragma once
#include "..\Component\Behaviour.h"
#include "..\..\Header\Graphics\CBuffer.h"
#include "..\..\Header\Math\Transform.h"
#include <vector>

namespace GatesEngine
{
	class GameObjectManager;
	class GameObject
	{
	private:
		std::vector<Component*> components;
		std::vector<Behaviour*> behaviors;
		GameObjectManager* manager;
		Math::Transform transform;
		const char* name;
		const char* tag;
	public:
		GameObject();
		GameObject(const char* name, const char* tag = "none");
		~GameObject();
		void Start();
		void Update();

		Math::Transform& GetTransform();
		void SetManager(GameObjectManager* manager);
		GameObjectManager* GetManager();

		template <typename T>
		T* AddComponent();
		template <typename T>
		T* AddBehavior();
		template <typename T>
		T* GetComponent();
	};
	template<typename T>
	inline T* GameObject::AddComponent()
	{
		T* t = new T();
		//Componentクラスから派生したものかチェック
		Component* pComponent = static_cast<Component*>(t);
		if (pComponent != nullptr)
		{
			components.push_back(pComponent);
			pComponent->SetGameObject(this);
			return t;
		}
		return nullptr;
	}
	template<typename T>
	inline T* GameObject::AddBehavior()
	{
		T* t = new T();
		//Componentクラスから派生したものかチェック
		Behaviour* pComponent = static_cast<Behaviour*>(t);
		if (pComponent != nullptr)
		{
			behaviors.push_back(pComponent);
			pComponent->SetGameObject(this);
			return t;
		}
		return nullptr;
	}
	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (int i = 0; i < (int)components.size(); i++)
		{
			T* component = dynamic_cast<T*>(components[i]);
			if (component != nullptr)
			{
				return component;
			}
		}
		return nullptr;
	}
}
