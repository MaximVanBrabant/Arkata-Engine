#pragma once
#include "Component.h"
#include "PlayerSM.h"

namespace dae
{
	class VersusEnemyState;
	class VersusEnemySM : public Component
	{
	public:
		VersusEnemySM(const std::shared_ptr<GameObject>& target);
		void SwitchState(const std::shared_ptr<VersusEnemyState>& newState);
		void Initialize() override;

		void Update(float deltaTime) override;
		void JumpIntoAir();
		void StandingStill();
		void ShootProjectile();
		void Displace();
		Direction GetDirection() const { return m_Direction; }
		void SetDirection(Direction direction) { m_Direction = direction; }

		const std::shared_ptr<VersusEnemyState>& GetIdleState() const { return m_Idle; }
		const std::shared_ptr<VersusEnemyState>& GetMoveState() const { return m_Move; }
		const std::shared_ptr<VersusEnemyState>& GetJumpState() const { return m_Jump; }

		bool ReadyToShoot() const { return m_CanShoot; }
		bool IsImmune() const { return m_IsImmune; }

		void SetImmune(bool enable) { m_IsImmune = enable; }

		const std::weak_ptr<GameObject>& GetTarget() const { return m_Target; }

	private:
		std::shared_ptr<VersusEnemyState> m_Idle;
		std::shared_ptr<VersusEnemyState> m_Move;
		std::shared_ptr<VersusEnemyState> m_Jump;

		std::shared_ptr<VersusEnemyState> m_CurrentVersusEnemyState;

		bool m_CanShoot = true;
		const float m_ShootCooldown = 0.5f;
		float m_CurrentShotCooldown = 0.f;

		bool m_IsImmune = false;
		const float m_ImmuneCooldown = 0.5f;
		float m_CurrentImmuneCooldown = 0.f;


		Direction m_Direction = Direction::right;

		std::weak_ptr<GameObject> m_Target;
	};
}