#pragma once
#include "VersusEnemyState.h"
namespace dae
{
	class VersusEnemyJumpState : public VersusEnemyState
	{
	public:
		VersusEnemyJumpState(VersusEnemySM* versusEnemySM) :VersusEnemyState(versusEnemySM) {}
		void Entry() override;
		void Update(float deltaTime) override;
		void Exit() override {}
		void JumpIntoAir() override {};
		void StandingStill() override {};
		void ShootProjectile() override {};
		void Displace() override;
	private:
		const float m_JumpHeight = -250.f; // was -225f
		const float m_JumpMoveVelocity = 150.f;
	};
}

