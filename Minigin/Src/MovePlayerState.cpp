#include "MiniginPCH.h"
#include "MovePlayerState.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "PlayerSM.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ColliderComponent.h"
#include "SelfDestructComponent.h"
#include "BellComponent.h"

void dae::MovePlayerState::Entry()
{
	if (m_PlayerSM->m_Owner->HasComponent<SpriteComponent>())
	{

		if (m_PlayerSM->GetDirection() == Direction::left)
		{
			m_PlayerSM->m_Owner->GetComponent<SpriteComponent>()->Play("moving_left");
			m_pTransform->SetVelocity(-m_MovingSpeed, m_pTransform->GetVelocity().y);
		}
		else if (m_PlayerSM->GetDirection() == Direction::right)
		{
			m_PlayerSM->m_Owner->GetComponent<SpriteComponent>()->Play("moving_right");

			m_pTransform->SetVelocity(m_MovingSpeed, m_pTransform->GetVelocity().y);
		}



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
		//put these vars inside playerSM
		float offset = 20.f;
		float shootingVelocity = 100.f;
		if (m_PlayerSM->GetDirection() == Direction::left)
		{
			sprite->Play("shoot_left");
			offset = -offset;
			shootingVelocity = -shootingVelocity;

		}
		else
		{
			sprite->Play("shoot_right");
		}

		//create bell
		//we can also set velocity in bubble
		std::shared_ptr<GameObject> bubble{ std::make_shared<GameObject>("bubble", false) };
		bubble->AddComponent<Transform>(static_cast<int>(m_pTransform->GetPosition().x + offset),static_cast<int>( m_pTransform->GetPosition().y),static_cast<int>( shootingVelocity), 0, 32, 32, 1);
		bubble->AddComponent<ColliderComponent>("BUBBLE");
		bubble->AddComponent<SpriteComponent>("bubble");
		bubble->AddComponent<SelfDestructComponent>(4.f);
		bubble->AddComponent<BellComponent>(shootingVelocity);
		SceneManager::GetInstance().GetActiveScene()->Add(bubble);
	}
}

void dae::MovePlayerState::Displace()
{
	//move
	if (m_PlayerSM->GetDirection() == Direction::left)
	{
		m_PlayerSM->m_Owner->GetComponent<SpriteComponent>()->Play("moving_left");
		m_pTransform->SetVelocity(-m_MovingSpeed, m_pTransform->GetVelocity().y);
	}
	else if (m_PlayerSM->GetDirection() == Direction::right)
	{
		m_PlayerSM->m_Owner->GetComponent<SpriteComponent>()->Play("moving_right");

		m_pTransform->SetVelocity(m_MovingSpeed, m_pTransform->GetVelocity().y);
	}
}
