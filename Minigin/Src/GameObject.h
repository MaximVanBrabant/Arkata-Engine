#pragma once
#include "Transform.h"

class Component;

namespace dae
{
	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render() const;
		void Destroy();

		//Transform
		//const Transform& GetTransform() const;

		GameObject();
		GameObject(const std::string& name);
		~GameObject() = default;


		GameObject(const GameObject& other);
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		const std::string& GetName() const { return m_Name; }
		bool IsActive() const { return m_IsActive; }

		template<typename T, typename... TArgs>
		T& AddComponent(TArgs&&... args)
		{
			std::shared_ptr<T> newComponent = std::make_shared<T>(std::forward<TArgs>(args)...);
			newComponent->SetGameObject(*this);
			m_pComponents.push_back(newComponent);
			newComponent->Initialize();
			return *newComponent;

		}

	private:
		bool m_IsActive;
		std::vector<std::shared_ptr<Component>> m_pComponents;
		std::string m_Name;
	};
}
