#pragma once
#include "EnemyState.h"
namespace dae
{
	class SeekEnemyState : public EnemyState
	{
	public:
		SeekEnemyState(EnemySM* enemySM) : EnemyState(enemySM), m_CurrentMovementSpeed{} {}
		void Entry() override;
		void Update(float deltaTime) override;
		void JumpIntoAir() override;
		void Exit() override {}
		const glm::vec2& GetDisplacement() const { return m_Displacement; }

	private:
		bool m_IsSpawned = false;
		float m_CurrentMovementSpeed;
		const float m_MaxMovementSpeed = 75.f;
		glm::vec2 m_Displacement;


		const float m_CooldownTime = 2.f;
		float m_CurrentCooldown = 0.0f;
	};
}