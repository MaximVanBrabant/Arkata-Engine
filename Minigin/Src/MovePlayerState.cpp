#include "MiniginPCH.h"
#include "MovePlayerState.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "PlayerSM.h"

void dae::MovePlayerState::Entry()
{
	if (m_PlayerSM->m_Owner->HasComponent<SpriteComponent>())
	{
		auto sprite = m_PlayerSM->m_Owner->GetComponent<SpriteComponent>();
		sprite->Play("moving");
	}
}

void dae::MovePlayerState::JumpIntoAir()
{
	//switch to jumping
	m_PlayerSM->SwitchState(m_PlayerSM->GetJumpState());
}

void dae::MovePlayerState::StandingStill()
{
	//switch to idle
	m_PlayerSM->SwitchState(m_PlayerSM->GetIdleState());
}

void dae::MovePlayerState::ShootBell(Direction direction)
{
	//shoot a bell
	UNREFERENCED_PARAMETER(direction);
	if (m_PlayerSM->m_Owner->HasComponent<SpriteComponent>())
	{
		auto sprite = m_PlayerSM->m_Owner->GetComponent<SpriteComponent>();
		sprite->Play("shoot");
	}
}

void dae::MovePlayerState::Displace(Direction direction)
{
	//move
	if (direction == Direction::left)
	{
		m_pTransform->SetVelocity(-m_MovingSpeed, m_pTransform->GetVelocity().y);
	}
	else if (direction == Direction::right)
	{
		m_pTransform->SetVelocity(m_MovingSpeed, m_pTransform->GetVelocity().y);
	}
}
