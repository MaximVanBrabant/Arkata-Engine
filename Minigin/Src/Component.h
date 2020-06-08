#pragma once
//#include "GameObject.h"
#include <memory>
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
		GameObject* m_Owner = nullptr;
		bool m_IsActive = true;
	private:
	};
}

