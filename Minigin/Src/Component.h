#pragma once
#include "GameObject.h"
#include <memory>
namespace dae
{
	//class GameObject;
	class Component
	{
	public:
		virtual ~Component() {}
		virtual void Initialize() {}
		virtual void Update(float deltaTime) { UNREFERENCED_PARAMETER(deltaTime); }
		virtual void Render() const {}
		//const GameObject& GetGameObject() const { return m_Owner }
		//void SetGameObject(std::shared_ptr<GameObject> gameObject ) { m_Owner = gameObject; }
		GameObject* m_Owner = nullptr;
		//GameObject m_Owner;
	private:
	};
}

