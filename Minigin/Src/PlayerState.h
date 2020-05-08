#pragma once
#include "PlayerSM.h"
#include "GameObject.h"
#include "Transform.h"
namespace dae
{
	class Transform;
	class SpriteComponent;
	enum class Direction;
	class PlayerState
	{
	public:
		PlayerState(PlayerSM* playerSM) :m_PlayerSM{ playerSM }, m_pTransform{ nullptr } {}
		void Initialize(){ m_pTransform = m_PlayerSM->m_Owner->GetComponent<Transform>(); }

		virtual void Entry() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Exit() = 0;
		virtual void JumpIntoAir() = 0;
		virtual void StandingStill() = 0;
		virtual void ShootBell(Direction direction) = 0;
		virtual void Displace(Direction direction) = 0;
	protected:
		PlayerSM* m_PlayerSM;
		Transform* m_pTransform;
	};
}

