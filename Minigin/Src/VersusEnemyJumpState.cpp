#include "MiniginPCH.h"
#include "VersusEnemyJumpState.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "VersusEnemySM.h"
#include "RigidBodyComponent.h"

void dae::VersusEnemyJumpState::Entry()
{

	if (m_VersusEnemySM->m_Owner->HasComponent<ColliderComponent>() && m_VersusEnemySM->m_Owner->HasComponent<RigidBodyComponent>())
	{
		auto collider = m_VersusEnemySM->m_Owner->GetComponent<ColliderComponent>();
		auto rigid = m_VersusEnemySM->m_Owner->GetComponent<RigidBodyComponent>();
		collider->SetIsGrounded(false);
		rigid->EnableGravity(true);

	}
	m_pTransform->SetVelocity(m_pTransform->GetVelocity().x, m_JumpHeight);
}

void dae::VersusEnemyJumpState::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_VersusEnemySM->m_Owner->HasComponent<ColliderComponent>())
	{
		auto collider = m_VersusEnemySM->m_Owner->GetComponent<ColliderComponent>();
		if (collider->GetIsGrounded())
		{
			if (m_pTransform->GetVelocity().x == 0)
			{
				m_VersusEnemySM->SwitchState(m_VersusEnemySM->GetIdleState());
			}
			else
			{
				m_VersusEnemySM->SwitchState(m_VersusEnemySM->GetMoveState());
			}
		}
	}
	else
	{
		std::cout << "this object: " << m_VersusEnemySM->m_Owner->GetName() << "should get a collider to not bug " << std::endl;
	}
}

void dae::VersusEnemyJumpState::Displace()
{
	//move like normal
	if (m_VersusEnemySM->GetDirection() == Direction::left)
	{
		m_pTransform->SetVelocity(-m_JumpMoveVelocity, m_pTransform->GetVelocity().y);
	}
	else if (m_VersusEnemySM->GetDirection() == Direction::right)
	{
		m_pTransform->SetVelocity(m_JumpMoveVelocity, m_pTransform->GetVelocity().y);
	}
}
