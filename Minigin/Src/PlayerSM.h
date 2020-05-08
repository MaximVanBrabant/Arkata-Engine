#pragma once
#include "Component.h"
//#include "PlayerState.h"

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
		void ShootBell(Direction direction) ; 
		void Displace(Direction direction);

		const std::shared_ptr<PlayerState>& GetIdleState() const { return m_Idle; }
		const std::shared_ptr<PlayerState>& GetMoveState() const { return m_Move; }
		const std::shared_ptr<PlayerState>& GetJumpState() const { return m_Jump; }


	private:
		std::shared_ptr<PlayerState> m_Idle; 
		std::shared_ptr<PlayerState> m_Move;
		std::shared_ptr<PlayerState> m_Jump;

		std::shared_ptr<PlayerState> m_CurrentPlayerState;
	};
}

