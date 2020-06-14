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
	
	if(!m_CanShoot && m_CurrentShotCooldown < m_ShootCooldown)
		m_CurrentShotCooldown += deltaTime;
	else if (m_CurrentShotCooldown >= m_ShootCooldown && !m_CanShoot)
	{
		m_CanShoot = true;
		m_CurrentShotCooldown = 0.0f;
	}

	if (m_IsImmune && m_CurrentImmuneCooldown < m_ImmuneCooldown)
	{
		m_CurrentImmuneCooldown += deltaTime;
	}
	else if(m_CurrentImmuneCooldown >= m_ImmuneCooldown && m_IsImmune)
	{
		m_IsImmune = false;
		m_CurrentImmuneCooldown = 0.0f;
	}


}

void dae::PlayerSM::JumpIntoAir()
{
	m_CurrentPlayerState->JumpIntoAir();
}
void dae::PlayerSM::StandingStill()
{
	m_CurrentPlayerState->StandingStill();
}
void dae::PlayerSM::ShootBell()
{
	m_CanShoot = false;
	m_CurrentPlayerState->ShootBell();
}
void dae::PlayerSM::Displace()
{
	m_CurrentPlayerState->Displace();
}