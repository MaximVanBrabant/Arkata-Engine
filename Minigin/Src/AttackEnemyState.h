#pragma once
#include "EnemyState.h"
namespace dae
{
	class AttackEnemyState : public EnemyState
	{
	public:
		AttackEnemyState(EnemySM* enemySM) : EnemyState(enemySM) {}
		void Entry() override;
		void JumpIntoAir() override { std::cout << "you are attacking" << std::endl; }
		void Update(float deltaTime) override;
		void TrapInBell() override;
		void Exit() override;
	private:
		const float m_AttackDuration = 0.5f;
		float m_CurrentDuration = 0.0f;

		const float m_DashSpeed = 200.f;
	};
}