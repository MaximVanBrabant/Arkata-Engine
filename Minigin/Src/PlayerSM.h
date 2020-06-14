#pragma once
#include "Component.h"

namespace dae
{
	enum class Direction
	{
		left,
		right
	};
	class PlayerState;
	class PlayerSM : public Component
	{
	public:
		PlayerSM();
		void SwitchState(const std::shared_ptr<PlayerState>& newState);
		void Initialize() override;

		void Update(float deltaTime) override;
		void JumpIntoAir();
		void StandingStill();
		void ShootBell();
		void Displace();
		Direction GetDirection() const { return m_Direction; }
		void SetDirection(Direction direction) { m_Direction = direction; }

		const std::shared_ptr<PlayerState>& GetIdleState() const { return m_Idle; }
		const std::shared_ptr<PlayerState>& GetMoveState() const { return m_Move; }
		const std::shared_ptr<PlayerState>& GetJumpState() const { return m_Jump; }

		bool ReadyToShoot() const { return m_CanShoot; }
		bool IsImmune() const { return m_IsImmune; }

		void SetImmune(bool enable) { m_IsImmune = enable; }

	private:
		std::shared_ptr<PlayerState> m_Idle; 
		std::shared_ptr<PlayerState> m_Move;
		std::shared_ptr<PlayerState> m_Jump;

		std::shared_ptr<PlayerState> m_CurrentPlayerState;

		bool m_CanShoot = true;
		const float m_ShootCooldown = 0.5f;
		float m_CurrentShotCooldown = 0.f;

		bool m_IsImmune = false;
		const float m_ImmuneCooldown = 0.5f;
		float m_CurrentImmuneCooldown = 0.f;


		Direction m_Direction = Direction::right;
	};
}

