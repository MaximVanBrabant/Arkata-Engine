#include "MiniginPCH.h"
#include "BellComponent.h"
#include "GameObject.h"
#include "Transform.h"

dae::BellComponent::BellComponent(float velocity)
	:m_RisingPhase{false}, m_pTransform{nullptr}, m_StartVelocity{velocity}
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
		//if startvelocity is less than 0 you have to increase the speed
		if (m_StartVelocity > 0)
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
		else
		{
			if (m_pTransform->GetVelocity().x > 0)
			{
				m_RisingPhase = true;
				m_pTransform->SetVelocity(0.f, -m_RisingVelocity);
			}
			else
			{
				m_pTransform->ApplyForceToVelocity(m_DecreasingSpeed * deltaTime, 0);
			}
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
