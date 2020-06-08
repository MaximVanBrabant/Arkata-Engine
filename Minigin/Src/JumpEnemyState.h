#pragma once
#include "EnemyState.h"
namespace dae
{
	class JumpEnemyState : public EnemyState
	{
	public:
		JumpEnemyState(EnemySM* enemySM) : EnemyState(enemySM){}
		void Entry() override;
		void Update(float deltaTime) override;
		void TrapInBell() override;
		void JumpIntoAir() override;
		void Exit() override {}
	private:


	};
}