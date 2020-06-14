#include "MiniginPCH.h"
#include "VersusEnemyMoveState.h"
#include "GameObject.h"
#include "VersusEnemySM.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ColliderComponent.h"
#include "SelfDestructComponent.h"
#include "SpriteComponent.h"

void dae::VersusEnemyMoveState::Entry()
{
	if (m_VersusEnemySM->m_Owner->HasComponent<SpriteComponent>())
	{

		if (m_VersusEnemySM->GetDirection() == Direction::left)
		{
			m_pTransform->SetVelocity(-m_MovingSpeed, m_pTransform->GetVelocity().y);
		}
		else if (m_VersusEnemySM->GetDirection() == Direction::right)
		{

			m_pTransform->SetVelocity(m_MovingSpeed, m_pTransform->GetVelocity().y);
		}



	}
}

void dae::VersusEnemyMoveState::JumpIntoAir()
{
	//switch to jumping
	m_VersusEnemySM->SwitchState(m_VersusEnemySM->GetJumpState());
}

void dae::VersusEnemyMoveState::StandingStill()
{
	//switch to idle
	m_VersusEnemySM->SwitchState(m_VersusEnemySM->GetIdleState());
}

void dae::VersusEnemyMoveState::ShootProjectile()
{
	glm::vec2 displacement = m_VersusEnemySM->GetTarget().lock()->GetComponent<Transform>()->GetPosition() - m_pTransform->GetPosition();


	//create bell
	std::shared_ptr<GameObject> projectile{ std::make_shared<GameObject>("bubble", false) };
	projectile->AddComponent<Transform>(static_cast<int>(m_pTransform->GetPosition().x), static_cast<int>(m_pTransform->GetPosition().y), static_cast<int>(displacement.x), static_cast<int>(displacement.y), 16, 16, 1);
	projectile->AddComponent<ColliderComponent>("PROJECTILE");
	projectile->AddComponent<SpriteComponent>("bullet");
	projectile->AddComponent<SelfDestructComponent>(4.f);

	SceneManager::GetInstance().GetActiveScene()->Add(projectile);
	
}

void dae::VersusEnemyMoveState::Displace()
{
	//move
	if (m_VersusEnemySM->GetDirection() == Direction::left)
	{
		m_pTransform->SetVelocity(-m_MovingSpeed, m_pTransform->GetVelocity().y);
	}
	else if (m_VersusEnemySM->GetDirection() == Direction::right)
	{

		m_pTransform->SetVelocity(m_MovingSpeed, m_pTransform->GetVelocity().y);
	}
}
