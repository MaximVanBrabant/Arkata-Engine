#pragma once
#include "VersusEnemyState.h"
namespace dae
{
	class VersusEnemyMoveState : public VersusEnemyState
	{
	public:
		VersusEnemyMoveState(VersusEnemySM* versusEnemySM) :VersusEnemyState(versusEnemySM) {}
		void Entry() override;
		void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); }
		void Exit() override {}
		void JumpIntoAir() override;
		void StandingStill() override;
		void ShootProjectile() override;
		void Displace() override;
	private:
		const float m_MovingSpeed = 200.f;
	};
}

