#include "MiniginPCH.h"
#include "SelfDestructComponent.h"
#include "GameObject.h"

dae::SelfDestructComponent::SelfDestructComponent(float time)
	:m_CurrentTime{0.0f}, m_TimeToDestruct{time}
{
}

void dae::SelfDestructComponent::Update(float deltaTime)
{
	if (m_CurrentTime < m_TimeToDestruct)
	{
		m_CurrentTime += deltaTime;
	}
	else
	{
		m_Owner->Destroy();
	}
}

