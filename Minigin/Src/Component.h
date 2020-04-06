#pragma once
#include "GameObject.h"
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual ~Component() {}
		virtual void Initialize() {}
		virtual void Update(float deltaTime) { UNREFERENCED_PARAMETER(deltaTime); }
		virtual void Render() const {}
		const std::shared_ptr<GameObject>& GetGameObject() const { return m_Owner; }
		void SetGameObject(const GameObject& gameObject) { m_Owner = std::move(std::make_shared<GameObject>(gameObject)); }
	private:
		std::shared_ptr<GameObject> m_Owner;
	};
}

