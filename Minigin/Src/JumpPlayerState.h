#pragma once
#include "PlayerState.h"
namespace dae
{
	class JumpPlayerState : public PlayerState
	{
	public:
		JumpPlayerState(PlayerSM* playerSM) :PlayerState(playerSM) {}
		void Entry() override;
		void Update(float deltaTime) override;
		void Exit() override {}
		void JumpIntoAir() override;
		void StandingStill() override;
		void ShootBell(Direction direction) override;
		void Displace(Direction direction) override;
	private:
		const float m_JumpHeight = -250.f; // was -225f
		const float m_JumpMoveVelocity = 150.f;
	};
}

