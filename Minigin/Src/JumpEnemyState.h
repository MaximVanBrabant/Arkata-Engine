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
		//here i can give something as a parameter
		void JumpIntoAir() override;
		void Exit() override {}
	private:


	};
}