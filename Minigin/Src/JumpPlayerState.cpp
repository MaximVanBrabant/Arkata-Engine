#include "MiniginPCH.h"
#include "JumpPlayerState.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "PlayerSM.h"
#include "RigidBodyComponent.h"

void dae::JumpPlayerState::Entry()
{
	if (m_PlayerSM->m_Owner->HasComponent<SpriteComponent>())
	{
		auto sprite = m_PlayerSM->m_Owner->GetComponent<SpriteComponent>();
		sprite->Play("jumping");
	}
	if (m_PlayerSM->m_Owner->HasComponent<ColliderComponent>() && m_PlayerSM->m_Owner->HasComponent<RigidBodyComponent>())
	{
		auto collider = m_PlayerSM->m_Owner->GetComponent<ColliderComponent>();
		auto rigid = m_PlayerSM->m_Owner->GetComponent<RigidBodyComponent>();
		collider->SetIsGrounded(false);
		rigid->EnableGravity(true);
		
	}
	m_pTransform->SetVelocity(m_pTransform->GetVelocity().x, m_JumpHeight);
}

void dae::JumpPlayerState::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_PlayerSM->m_Owner->HasComponent<ColliderComponent>())
	{
		auto collider = m_PlayerSM->m_Owner->GetComponent<ColliderComponent>();
		if (collider->GetIsGrounded())
		{
			if (m_pTransform->GetVelocity().x == 0)
			{
				m_PlayerSM->SwitchState(m_PlayerSM->GetIdleState());
			}
			else
			{
				m_PlayerSM->SwitchState(m_PlayerSM->GetMoveState());
			}
		}
	}
	else
	{
		std::cout << "this object: " << m_PlayerSM->m_Owner->GetName() << "should get a collider to not bug " << std::endl;
	}
}

void dae::JumpPlayerState::JumpIntoAir()
{
	std::cout << "we are already jumping" << std::endl;
}

void dae::JumpPlayerState::StandingStill()
{
	std::cout << "im in the air without input" << std::endl;
}

void dae::JumpPlayerState::ShootBell(Direction direction)
{
	std::cout << "we cant shoot while in the air" << std::endl;
	UNREFERENCED_PARAMETER(direction);
}

void dae::JumpPlayerState::Displace(Direction direction)
{
	//move like normal
	if (direction == Direction::left)
	{
		m_pTransform->SetVelocity(-m_JumpMoveVelocity, m_pTransform->GetVelocity().y);
	}
	else if (direction == Direction::right)
	{
		m_pTransform->SetVelocity(m_JumpMoveVelocity, m_pTransform->GetVelocity().y);
	}
}
