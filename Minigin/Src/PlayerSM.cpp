#include "MiniginPCH.h"
#include "PlayerSM.h"
#include "PlayerState.h"
#include "IdlePlayerState.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "MovePlayerState.h"
#include "JumpPlayerState.h"

dae::PlayerSM::PlayerSM()
	:m_Idle{std::make_shared<IdlePlayerState>(this)}, m_Move{std::make_shared<MovePlayerState>(this)}, m_Jump{std::make_shared<JumpPlayerState>(this)}
{
}

void dae::PlayerSM::SwitchState(const std::shared_ptr<PlayerState>& newState)
{

	if (m_CurrentPlayerState != nullptr)
	{
		m_CurrentPlayerState->Exit();
	}

	m_CurrentPlayerState = newState;
	m_CurrentPlayerState->Entry();
}

void dae::PlayerSM::Initialize()
{
	SwitchState(m_Idle);
	m_Idle->Initialize();
	m_Jump->Initialize();
	m_Move->Initialize();
}

void dae::PlayerSM::Update(float deltaTime)
{
	m_CurrentPlayerState->Update(deltaTime);
}

void dae::PlayerSM::JumpIntoAir()
{
	m_CurrentPlayerState->JumpIntoAir();
}
void dae::PlayerSM::StandingStill()
{
	m_CurrentPlayerState->StandingStill();
}
void dae::PlayerSM::ShootBell(Direction direction)
{
	m_CurrentPlayerState->ShootBell(direction);
}
void dae::PlayerSM::Displace(Direction direction)
{
	m_CurrentPlayerState->Displace(direction);
}