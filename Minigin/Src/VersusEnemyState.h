#pragma once
#include "VersusEnemySM.h"
#include "GameObject.h"
#include "Transform.h"
namespace dae
{
	class Transform;
	class SpriteComponent;
	class VersusEnemyState
	{
	public:
		VersusEnemyState(VersusEnemySM* versusEnemySm) :m_VersusEnemySM{ versusEnemySm }, m_pTransform{ nullptr }{}
		void Initialize() { m_pTransform = m_VersusEnemySM->m_Owner->GetComponent<Transform>(); }

		virtual void Entry() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Exit() = 0;
		virtual void JumpIntoAir() = 0;
		virtual void StandingStill() = 0;
		virtual void ShootProjectile() = 0;
		virtual void Displace() = 0;
	protected:
		VersusEnemySM* m_VersusEnemySM;
		Transform* m_pTransform;
	};
}
