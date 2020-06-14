#include "MiniginPCH.h"
#include "VersusEnemyIdleState.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "PlayerSM.h"
#include "ColliderComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SelfDestructComponent.h"
#include "BellComponent.h"

void dae::VersusEnemyIdleState::Entry()
{
	if (m_pTransform != nullptr)
	{
		m_pTransform->SetVelocity(0.0f, m_pTransform->GetVelocity().y);
	}
}

void dae::VersusEnemyIdleState::JumpIntoAir()
{
	m_VersusEnemySM->SwitchState(m_VersusEnemySM->GetJumpState());
}

void dae::VersusEnemyIdleState::ShootProjectile()
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

void dae::VersusEnemyIdleState::Displace()
{
	m_VersusEnemySM->SwitchState(m_VersusEnemySM->GetMoveState());
}

