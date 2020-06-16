#pragma once
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "Transform.h"

namespace dae
{
	class Component;
	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render() const;
		void Destroy();

		GameObject();
		GameObject(const std::string& name, bool isStatic);
		virtual ~GameObject();

		//need to use raw pointers sometimes to make sure i dont make any copies of the gameObject (see documentation)
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		const std::string& GetName() const { return m_Name; }
		bool IsActive() const { return m_IsActive; }
		bool IsStatic() const { return m_IsStatic; }

		template<typename T, typename... TArgs>
		T& AddComponent(TArgs&&... args)
		{
			std::shared_ptr<T> newComponent = std::make_shared<T>(std::forward<TArgs>(args)...);
			newComponent->m_Owner = this;
			m_pComponents.push_back(newComponent);
			m_ComponentTypeMap[&typeid(*newComponent)] = newComponent;
			newComponent->Initialize();
			return *newComponent;
		}

		//return a raw pointer instead of a smart pointer because otherwise it will make a copy of the object so the new smart pointer would point to the new gameObject and you don't want that
		template<typename T>
		T* GetComponent()
		{
			return dynamic_cast<T*>(m_ComponentTypeMap[&typeid(T)].get());
		}

		template<typename T>
		bool HasComponent() const
		{
			//this is needed because of threading
			if (this != nullptr)
			{
				for (auto& pair : m_ComponentTypeMap)
				{
					if (typeid(T).name() == pair.first->name())
					{
						return true;
					}
				}
				return false;
			}
			return false;
			//throw exeption
		}


		void ListComponents() const;

	private:
		bool m_IsActive;
		std::vector<std::shared_ptr<Component>> m_pComponents;
		std::map<const type_info*, std::shared_ptr<Component>> m_ComponentTypeMap;
		std::string m_Name;
		bool m_IsStatic; //this gameobject wont be used to check for collisions
	};
}
