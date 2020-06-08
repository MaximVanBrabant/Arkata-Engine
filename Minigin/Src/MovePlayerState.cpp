#include "MiniginPCH.h"
#include "MovePlayerState.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "PlayerSM.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ColliderComponent.h"

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

void dae::MovePlayerState::ShootBell()
{
	//shoot a bell
	if (m_PlayerSM->m_Owner->HasComponent<SpriteComponent>())
	{
		auto sprite = m_PlayerSM->m_Owner->GetComponent<SpriteComponent>();
		sprite->Play("shoot");
		float offset = 10.f;
		//ump this up
		float shootingVelocity = 100.f;

		if (m_PlayerSM->GetDirection() == Direction::left)
		{
			offset = -offset;
			shootingVelocity = -shootingVelocity;
		}

		//create bell
		std::shared_ptr<GameObject> bubble{ std::make_shared<GameObject>("bubble", false) };
		bubble->AddComponent<Transform>(static_cast<int>(m_pTransform->GetPosition().x + offset),static_cast<int>( m_pTransform->GetPosition().y),static_cast<int>( shootingVelocity), 0, 32, 32, 1);
		bubble->AddComponent<ColliderComponent>("BUBBLE");
		bubble->AddComponent<SpriteComponent>("bubble");
		SceneManager::GetInstance().GetActiveScene()->Add(bubble);


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
