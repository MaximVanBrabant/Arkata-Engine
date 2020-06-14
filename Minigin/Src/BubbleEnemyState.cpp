#include "MiniginPCH.h"
#include "BubbleEnemyState.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"

void dae::BubbleEnemyState::Entry()
{
	m_TextureBubbleIndex = m_pTransform->m_Owner->GetComponent<SpriteComponent>()->AddTexture("bubble");
	m_pTransform->m_Owner->GetComponent<RigidBodyComponent>()->m_IsActive = false;
	m_pTransform->m_Owner->GetComponent<ColliderComponent>()->ChangeTag("BUBBLE_ENEMY");
	m_pTransform->SetVelocity(0, -m_FloatSpeed);
}

void dae::BubbleEnemyState::Update(float deltaTime)
{

	if (m_CurrentDuration < m_TrapDuration)
	{
		m_CurrentDuration += deltaTime;

	}
	else
	{
		m_CurrentDuration = 0.0f;
		m_pTransform->m_Owner->GetComponent<RigidBodyComponent>()->m_IsActive = true;
		m_pTransform->m_Owner->GetComponent<SpriteComponent>()->RemoveTexture(m_TextureBubbleIndex);
		m_pTransform->m_Owner->GetComponent<ColliderComponent>()->ChangeTag("ENEMY");
		m_pEnemySM->SwitchState(m_pEnemySM->GetSeekState());
	}


}
