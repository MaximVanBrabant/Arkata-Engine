#include "MiniginPCH.h"
#include "BubbleEnemyState.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"

void dae::BubbleEnemyState::Entry()
{
	m_pTransform->m_Owner->GetComponent<SpriteComponent>()->AddTexture("bubble");
	m_pTransform->m_Owner->GetComponent<RigidBodyComponent>()->m_IsActive = false;
	m_pTransform->m_Owner->GetComponent<ColliderComponent>()->ChangeTag("BUBBLE_ENEMY");
	m_pTransform->SetVelocity(0, -100.f);
}

void dae::BubbleEnemyState::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	std::cout << "im in bubble state" << std::endl;
}
