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
		void Exit() override {}
	private:

	};
}