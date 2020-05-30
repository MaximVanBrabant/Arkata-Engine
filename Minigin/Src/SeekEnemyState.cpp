#include "MiniginPCH.h"
#include "SeekEnemyState.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "EnemySM.h"
#include "ColliderComponent.h"

void dae::SeekEnemyState::Entry()
{
}

void dae::SeekEnemyState::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//TURN OFF\ON COLLISION WHEN NEEDED



	if (m_pEnemySM->GetTarget().expired())
	{
		std::cout << "enemy doenst have a target" << std::endl;
		return;
	}

	m_Displacement = m_pEnemySM->GetTarget().lock()->GetComponent<Transform>()->GetPosition() - m_pTransform->GetPosition();
	

	//for the very first time an enemy spawns let him first drop down before he chases his target
	auto collider = m_pEnemySM->m_Owner->GetComponent<ColliderComponent>();
	if (collider->GetIsGrounded() && !m_IsSpawned)
	{
		m_pEnemySM->SetRightFloorCollider(false);
		m_pEnemySM->SetLeftFloorCollider(false);
		m_pEnemySM->SetRightPlatformCollider(false);
		m_pEnemySM->SetLeftPlatformCollider(false);

		m_IsSpawned = true;
		if (m_Displacement.x > 0)
		{
			m_pEnemySM->SetRightFloorCollider(true);
			m_CurrentMovementSpeed = m_MaxMovementSpeed;
		}
		else
		{
			m_pEnemySM->SetLeftFloorCollider(true);
			m_CurrentMovementSpeed = -m_MaxMovementSpeed;
		}

		if (m_Displacement.y < 0)
		{
			m_pEnemySM->SetRightPlatformCollider(true);
			m_pEnemySM->SetLeftPlatformCollider(true);
		}
		
	}


	//Basic Seek behavior

	if (m_Displacement.x > 0 && m_CurrentMovementSpeed < 0)
	{
		m_CurrentMovementSpeed *= -1;
		m_pEnemySM->SetLeftFloorCollider(false);
		m_pEnemySM->SetRightFloorCollider(true);
	}
	else if (m_Displacement.x < 0 && m_CurrentMovementSpeed > 0)
	{
		m_CurrentMovementSpeed *= -1;
		m_pEnemySM->SetLeftFloorCollider(true);
		m_pEnemySM->SetRightFloorCollider(false);
	}

	if (m_Displacement.y < 0)
	{
		m_pEnemySM->SetLeftPlatformCollider(true);
		m_pEnemySM->SetRightPlatformCollider(true);
	}

	if (m_Displacement.y > 0)
	{
		m_pEnemySM->SetLeftPlatformCollider(false);
		m_pEnemySM->SetRightPlatformCollider(false);
	}

	if (m_Displacement.y == 0)
	{
		m_pEnemySM->SetLeftPlatformCollider(false);
		m_pEnemySM->SetRightPlatformCollider(false);
	}

	if (abs(m_Displacement.x) < m_pEnemySM->GetToCloseDistance() && m_Displacement.y == 0)
	{
		//stop moving
		//go into attack
		std::cout << "i went into attack" << std::endl;
		m_pTransform->SetVelocity(0, m_pTransform->GetVelocity().y);
	}
	else
	{
		m_pTransform->SetVelocity(m_CurrentMovementSpeed, m_pTransform->GetVelocity().y);
	}

}

void dae::SeekEnemyState::JumpIntoAir()
{
	m_pEnemySM->SetLeftPlatformCollider(false);
	m_pEnemySM->SetRightPlatformCollider(false);
	m_pEnemySM->SwitchState(m_pEnemySM->GetJumpState());
}
