#include "MiniginPCH.h"
#include "AttackEnemyState.h"
#include "EnemySM.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "SelfDestructComponent.h"

void dae::AttackEnemyState::Entry()
{
	if (m_pEnemySM->GetEnemyType() == EnemyType::Throw)
	{
		//to avoid collisions with the enemy itself
		float offset = 32.f;
		if (m_pTransform->GetVelocity().x < 0)
		{
			offset = -offset;
		}

		//use the magnitude of the displacement to create the behavior of fast projectiles when far away but slow projectiles when close to player
		glm::vec2 displacement = m_pEnemySM->GetTarget().lock()->GetComponent<Transform>()->GetPosition() - m_pTransform->GetPosition();

		auto& scene = SceneManager::GetInstance().GetActiveScene();

		std::shared_ptr<GameObject> bullet = std::make_shared<GameObject>("bullet", false);
		bullet->AddComponent<Transform>(static_cast<int>(m_pTransform->GetPosition().x + offset),static_cast<int>( m_pTransform->GetPosition().y), static_cast<int>(displacement.x), static_cast<int>(displacement.y), 16, 16, 1);
		bullet->AddComponent<ColliderComponent>("PROJECTILE");
		bullet->AddComponent<SpriteComponent>("bullet");
		bullet->AddComponent<SelfDestructComponent>(5.f);
		scene->Add(bullet);


		m_pEnemySM->SwitchState(m_pEnemySM->GetSeekState());
	}
}

void dae::AttackEnemyState::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_pEnemySM->GetEnemyType() == EnemyType::Charge)
	{
		if (m_CurrentDuration < m_AttackDuration)
		{
			m_CurrentDuration += deltaTime;
			if (m_pTransform->GetVelocity().x > 0)
			{
				m_pTransform->SetVelocity(m_DashSpeed, m_pTransform->GetVelocity().y);
			}
			else if (m_pTransform->GetVelocity().x < 0)
			{
				m_pTransform->SetVelocity(-m_DashSpeed, m_pTransform->GetVelocity().y);
			}

		}
		else
		{
			//attack is over
			m_CurrentDuration = 0.0f;
			m_pEnemySM->SwitchState(m_pEnemySM->GetSeekState());
		}
	}

}

void dae::AttackEnemyState::TrapInBell()
{
	m_pEnemySM->SwitchState(m_pEnemySM->GetBubbleState());
}

void dae::AttackEnemyState::Exit()
{
	m_pEnemySM->SetHasAttacked(true);
}
