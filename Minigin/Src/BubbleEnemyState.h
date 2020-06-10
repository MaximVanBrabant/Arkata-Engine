#pragma once
#include "EnemyState.h"

namespace dae
{
	class BubbleEnemyState : public EnemyState
	{
	public:
		BubbleEnemyState(EnemySM* enemySM) : EnemyState(enemySM) {}
		void Entry() override;
		void JumpIntoAir() override {}
		void Update(float deltaTime) override;
		void TrapInBell() override { std::cout << "already in bell" << std::endl; }
		void Exit() override {}
	private: 
		float m_FloatSpeed = 50.f;
		float m_TrapDuration = 4.f;
		float m_CurrentDuration = 0.f;

		int m_TextureBubbleIndex;
	};
}