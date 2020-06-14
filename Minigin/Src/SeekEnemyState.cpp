#include "MiniginPCH.h"
#include "SeekEnemyState.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "EnemySM.h"
#include "ColliderComponent.h"
#include "InputManager.h"

void dae::SeekEnemyState::Entry()
{
}

void dae::SeekEnemyState::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_pEnemySM->GetTarget().expired())
	{
		if (InputManager::GetInstance().GetSecondDino() != nullptr)
		{
			m_pEnemySM->SetTarget(InputManager::GetInstance().GetSecondDino());
		}
		else
		{
			m_pEnemySM->SetRightFloorCollider(false);
			m_pEnemySM->SetLeftFloorCollider(false);
			m_pEnemySM->SetRightPlatformCollider(false);
			m_pEnemySM->SetLeftPlatformCollider(false);
			m_pEnemySM->SetLeftWallCollider(false);
			m_pEnemySM->SetRightWallCollider(false);
			m_pTransform->SetVelocity(0, m_pTransform->GetVelocity().y);
			return;
		}
	}

	//attack cooldown
	if (m_pEnemySM->GetHasAttacked())
	{
		if (m_CurrentCooldown < m_CooldownTime)
		{
			m_CurrentCooldown += deltaTime;
		}
		else
		{
			m_CurrentCooldown = 0.0f;
			m_pEnemySM->SetHasAttacked(false);
		}
	}
	
	m_Displacement = m_pEnemySM->GetTarget().lock()->GetComponent<Transform>()->GetPosition() - m_pTransform->GetPosition();
	
	//inverse movement because of wall detection / if enemies collid
	if (m_pEnemySM->GetInverseMovement())
	{
		if (m_pTransform->GetVelocity().x < 0)
		{
			m_pEnemySM->SetLeftWallCollider(false);
			m_pEnemySM->SetRightWallCollider(true);
			if (!m_pEnemySM->GetRightFloorCollider()->GetEnabled())
			{
				m_pEnemySM->SetLeftFloorCollider(false);
				m_pEnemySM->SetRightFloorCollider(true);
			}

		}
		else if (m_pTransform->GetVelocity().x > 0)
		{
			m_pEnemySM->SetLeftWallCollider(true);
			m_pEnemySM->SetRightWallCollider(false);
			if (!m_pEnemySM->GetLeftFloorCollider()->GetEnabled())
			{
				m_pEnemySM->SetLeftFloorCollider(true);
				m_pEnemySM->SetRightFloorCollider(false);
			}
		}


		m_pEnemySM->SetInverseMovement(false);
		m_CurrentMovementSpeed *= -1;
	}


	//for the very first time an enemy spawns let him first drop down before he chases his target
	auto collider = m_pEnemySM->m_Owner->GetComponent<ColliderComponent>();
	if (collider->GetIsGrounded() && !m_IsSpawned)
	{
		m_pEnemySM->SetRightFloorCollider(false);
		m_pEnemySM->SetLeftFloorCollider(false);
		m_pEnemySM->SetRightPlatformCollider(false);
		m_pEnemySM->SetLeftPlatformCollider(false);
		m_pEnemySM->SetLeftWallCollider(false);
		m_pEnemySM->SetRightWallCollider(false);

		m_IsSpawned = true;

		if (m_Displacement.x > 0)
		{
			m_pEnemySM->SetRightFloorCollider(true);
			m_pEnemySM->SetRightWallCollider(true);
			m_CurrentMovementSpeed = m_MaxMovementSpeed;
		}
		else
		{
			m_pEnemySM->SetLeftFloorCollider(true);
			m_pEnemySM->SetLeftWallCollider(true);
			m_CurrentMovementSpeed = -m_MaxMovementSpeed;
		}

		if (m_Displacement.y < 0)
		{
			m_pEnemySM->SetRightPlatformCollider(true);
			m_pEnemySM->SetLeftPlatformCollider(true);
		}

		m_pTransform->SetVelocity(m_CurrentMovementSpeed, m_pTransform->GetVelocity().y);
		
	}

	//Basic Seek behavior

	if (m_Displacement.x > 0 && m_CurrentMovementSpeed < 0 && m_Displacement.y == 0)
	{
		m_CurrentMovementSpeed *= -1;
		m_pEnemySM->SetLeftFloorCollider(false);
		m_pEnemySM->SetLeftWallCollider(false);
		m_pEnemySM->SetRightFloorCollider(true);
		m_pEnemySM->SetRightWallCollider(true);

		m_pEnemySM->SetLeftPlatformCollider(false);
		m_pEnemySM->SetRightPlatformCollider(false);
	}
	else if (m_Displacement.x < 0 && m_CurrentMovementSpeed > 0 && m_Displacement.y == 0)
	{
		m_CurrentMovementSpeed *= -1;
		m_pEnemySM->SetLeftFloorCollider(true);
		m_pEnemySM->SetLeftWallCollider(true);
		m_pEnemySM->SetRightFloorCollider(false);
		m_pEnemySM->SetRightWallCollider(false);

		m_pEnemySM->SetLeftPlatformCollider(false);
		m_pEnemySM->SetRightPlatformCollider(false);
	}

	//enemy below the player
	if (m_Displacement.y < 0)
	{
		if (m_CurrentMovementSpeed > 0)
		{
			m_pEnemySM->SetRightPlatformCollider(true);
			m_pEnemySM->SetRightFloorCollider(true);
			m_pEnemySM->SetLeftFloorCollider(false);
		}
		else
		{
			m_pEnemySM->SetLeftPlatformCollider(true);
			m_pEnemySM->SetLeftFloorCollider(true);
			m_pEnemySM->SetRightFloorCollider(false);
		}
	}
	//enemy above the player
	if(m_Displacement.y > 0)
	{
		m_pEnemySM->SetLeftPlatformCollider(false);
		m_pEnemySM->SetRightPlatformCollider(false);
		m_pEnemySM->SetLeftFloorCollider(false);
		m_pEnemySM->SetRightFloorCollider(false);
	}

	m_pTransform->SetVelocity(m_CurrentMovementSpeed, m_pTransform->GetVelocity().y);


	if (m_pEnemySM->GetEnemyType() == EnemyType::Charge)
	{
		if (abs(m_Displacement.x) < m_pEnemySM->GetToCloseMeleeDistance() && m_Displacement.y == 0 && !m_pEnemySM->GetHasAttacked())
		{
			//go into attack
			m_pEnemySM->SetLeftPlatformCollider(false);
			m_pEnemySM->SetRightPlatformCollider(false);
			m_pEnemySM->SetLeftFloorCollider(false);
			m_pEnemySM->SetRightFloorCollider(false);

			m_pEnemySM->SwitchState(m_pEnemySM->GetAttackState());
		}
	}
	else if (m_pEnemySM->GetEnemyType() == EnemyType::Throw)
	{
		if (abs(m_Displacement.y) < m_pEnemySM->GetToCloseRangedDistance() && !m_pEnemySM->GetHasAttacked() && m_IsSpawned)
		{
			m_pEnemySM->SetLeftPlatformCollider(false);
			m_pEnemySM->SetRightPlatformCollider(false);
			m_pEnemySM->SetLeftFloorCollider(false);
			m_pEnemySM->SetRightFloorCollider(false);

			m_pEnemySM->SwitchState(m_pEnemySM->GetAttackState());
		}
	}

}

void dae::SeekEnemyState::TrapInBell()
{
	m_pEnemySM->SwitchState(m_pEnemySM->GetBubbleState());
}

void dae::SeekEnemyState::JumpIntoAir()
{
	m_pEnemySM->SetLeftPlatformCollider(false);
	m_pEnemySM->SetRightPlatformCollider(false);
	m_pEnemySM->SwitchState(m_pEnemySM->GetJumpState());
}
