#include "MiniginPCH.h"
#include "JumpEnemyState.h"
#include "EnemySM.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"

void dae::JumpEnemyState::Entry()
{
	if (m_pEnemySM->m_Owner->HasComponent<ColliderComponent>() && m_pEnemySM->m_Owner->HasComponent<RigidBodyComponent>())
	{
		auto collider = m_pEnemySM->m_Owner->GetComponent<ColliderComponent>();
		auto rigid = m_pEnemySM->m_Owner->GetComponent<RigidBodyComponent>();
		collider->SetIsGrounded(false);
		rigid->EnableGravity(true);

	}
	m_pTransform->SetVelocity(m_pTransform->GetVelocity().x, m_pEnemySM->GetJumpHeight());

}

void dae::JumpEnemyState::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_pEnemySM->m_Owner->HasComponent<ColliderComponent>())
	{
		auto collider = m_pEnemySM->m_Owner->GetComponent<ColliderComponent>();
		if (collider->GetIsGrounded())
		{
			m_pEnemySM->SwitchState(m_pEnemySM->GetSeekState());
		}
	}

}

void dae::JumpEnemyState::JumpIntoAir()
{
	std::cout << "you already are jumping " << std::endl;
}
