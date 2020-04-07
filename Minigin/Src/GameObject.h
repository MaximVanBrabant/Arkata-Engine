#pragma once
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "Pointer_Cast.h"

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
		GameObject(const std::string& name);
		virtual ~GameObject();

		//this gets executed when i cal SetGameObject on component
		GameObject(const GameObject& other);
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(GameObject&& other) = delete;

		const std::string& GetName() const { return m_Name; }
		bool IsActive() const { return m_IsActive; }

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


		void ListComponents() const;

	private:
		bool m_IsActive;
		std::vector<std::shared_ptr<Component>> m_pComponents;
		std::map<const type_info*, std::shared_ptr<Component>> m_ComponentTypeMap;
		std::string m_Name;
	};
}
