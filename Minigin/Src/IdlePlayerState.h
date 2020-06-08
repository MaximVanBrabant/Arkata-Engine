#pragma once
#include "PlayerState.h"
namespace dae
{
	class IdlePlayerState : public PlayerState
	{
	public:
		IdlePlayerState(PlayerSM* playerSM) :PlayerState(playerSM) {}
		void Entry() override;
		void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); }
		void Exit() override {}
		void JumpIntoAir() override;
		void StandingStill() override {};
		void ShootBell() override;
		void Displace(Direction direction) override;
	private:

	};
}

