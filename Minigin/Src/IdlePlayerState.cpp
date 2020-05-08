#include "MiniginPCH.h"
#include "IdlePlayerState.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "PlayerSM.h"

void dae::IdlePlayerState::Entry()
{
	if (m_PlayerSM->m_Owner->HasComponent<SpriteComponent>())
	{
		auto sprite = m_PlayerSM->m_Owner->GetComponent<SpriteComponent>();
		sprite->Play("idle");
	}
	if (m_pTransform != nullptr)
	{
		m_pTransform->SetVelocity(0.0f, m_pTransform->GetVelocity().y);
	}
}

void dae::IdlePlayerState::JumpIntoAir()
{
	m_PlayerSM->SwitchState(m_PlayerSM->GetJumpState());
}

void dae::IdlePlayerState::ShootBell(Direction direction)
{
	//instantiate object
	UNREFERENCED_PARAMETER(direction);
	if (m_PlayerSM->m_Owner->HasComponent<SpriteComponent>())
	{
		auto sprite = m_PlayerSM->m_Owner->GetComponent<SpriteComponent>();
		sprite->Play("shoot");
	}
}

void dae::IdlePlayerState::Displace(Direction direction)
{
	m_PlayerSM->SwitchState(m_PlayerSM->GetMoveState());
	UNREFERENCED_PARAMETER(direction);
}

