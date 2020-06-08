#pragma once
#include "EnemySM.h"
#include "GameObject.h"
#include "Transform.h"
namespace dae
{
	class Transform;
	class SpriteComponent;
	class EnemyState
	{
	public:
		EnemyState(EnemySM* pEnemySM) : m_pEnemySM{ pEnemySM }, m_pTransform{ nullptr }{}
		void Initialize() { m_pTransform = m_pEnemySM->m_Owner->GetComponent<Transform>(); }

		virtual void Entry() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void JumpIntoAir() = 0;
		virtual void TrapInBell() = 0;
		virtual void Exit() = 0;
	protected:
		EnemySM* m_pEnemySM;
		Transform* m_pTransform;
	};
}