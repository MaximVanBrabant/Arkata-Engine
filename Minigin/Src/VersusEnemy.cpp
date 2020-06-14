#include "MiniginPCH.h"
#include "VersusEnemySM.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "VersusEnemyIdleState.h"
#include "VersusEnemyJumpState.h"
#include "VersusEnemyMoveState.h"


dae::VersusEnemySM::VersusEnemySM(const std::shared_ptr<GameObject>& target)
	:m_Idle{ std::make_shared<VersusEnemyIdleState>(this) }, m_Move{ std::make_shared<VersusEnemyMoveState>(this) }, m_Jump{ std::make_shared<VersusEnemyJumpState>(this) }, m_Target{target}
{
}

void dae::VersusEnemySM::SwitchState(const std::shared_ptr<VersusEnemyState>& newState)
{

	if (m_CurrentVersusEnemyState != nullptr)
	{
		m_CurrentVersusEnemyState->Exit();
	}

	m_CurrentVersusEnemyState = newState;
	m_CurrentVersusEnemyState->Entry();
}

void dae::VersusEnemySM::Initialize()
{
	SwitchState(m_Idle);
	m_Idle->Initialize();
	m_Jump->Initialize();
	m_Move->Initialize();
}

void dae::VersusEnemySM::Update(float deltaTime)
{
	m_CurrentVersusEnemyState->Update(deltaTime);

	if (!m_CanShoot && m_CurrentShotCooldown < m_ShootCooldown)
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
	else if (m_CurrentImmuneCooldown >= m_ImmuneCooldown && m_IsImmune)
	{
		m_IsImmune = false;
		m_CurrentImmuneCooldown = 0.0f;
	}


}

void dae::VersusEnemySM::JumpIntoAir()
{
	m_CurrentVersusEnemyState->JumpIntoAir();
}
void dae::VersusEnemySM::StandingStill()
{
	m_CurrentVersusEnemyState->StandingStill();
}
void dae::VersusEnemySM::ShootProjectile()
{
	m_CanShoot = false;
	m_CurrentVersusEnemyState->ShootProjectile();
}
void dae::VersusEnemySM::Displace()
{
	m_CurrentVersusEnemyState->Displace();
}