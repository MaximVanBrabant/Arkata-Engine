#include "MiniginPCH.h"
#include "BellComponent.h"
#include "GameObject.h"
#include "Transform.h"

dae::BellComponent::BellComponent()
	:m_RisingPhase{false}
{
}

void dae::BellComponent::Initialize()
{
	m_pTransform = m_Owner->GetComponent<Transform>();
}

void dae::BellComponent::Update(float deltaTime)
{
	if (!m_RisingPhase)
	{
		if (m_pTransform->GetVelocity().x < 0)
		{
			m_RisingPhase = true;
			m_pTransform->SetVelocity(0.f, -m_RisingVelocity);
		}
		else
		{
			m_pTransform->ApplyForceToVelocity(-m_DecreasingSpeed * deltaTime, 0);
		}
	}
	else if(m_RisingPhase)
	{
		if (m_pTransform->GetVelocity().y >= 0)
		{
			m_pTransform->SetVelocity(0, 0);
		}
		else
		{
			m_pTransform->ApplyForceToVelocity(0, m_DecreasingSpeed * deltaTime);
		}
	}
}
