#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Transform.h"
#include "Renderer.h"
#include "GameObject.h"
#include <SDL.h>
#include "Constants.h"
#include "RigidBodyComponent.h"
dae::ColliderComponent::ColliderComponent(const std::string& tag)
	:m_pTransform{ nullptr }, m_Collider{}, m_Tag{ tag }, m_OffsetX{}, m_OffsetY{}
{
}
void dae::ColliderComponent::Initialize()
{
	if (m_Owner->HasComponent<Transform>())
	{
		m_pTransform = m_Owner->GetComponent<Transform>();
	}
	else
	{
		std::cout << m_Owner->GetName() << " has no transform component attached to it" << std::endl;
	}
}

void dae::ColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	m_Collider.x = static_cast<int>(m_pTransform->GetPosition().x) + m_OffsetX;
	m_Collider.y = static_cast<int>(m_pTransform->GetPosition().y) + m_OffsetY;
	m_Collider.w = m_pTransform->GetWidth() * m_pTransform->GetScale();
	m_Collider.h = m_pTransform->GetHeight() * m_pTransform->GetScale();

	m_CenterX = m_Collider.x + m_Collider.w / 2.0f;
	m_CenterY = m_Collider.y + m_Collider.h / 2.0f;

	if (m_pTransform->GetPosition().y > WINDOWHEIGHT)
	{
		m_pTransform->SetPosition(m_pTransform->GetPosition().x,static_cast<float>(0-m_Collider.w));
	}

	if (m_pTransform->GetPosition().y + m_Collider.w < 0)
	{
		m_pTransform->SetPosition(m_pTransform->GetPosition().x, static_cast<float>(WINDOWHEIGHT));
	}
}

void dae::ColliderComponent::Render() const
{
	if (m_Enabled)
	{
		SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 255);
		//SDL_RenderDrawRect(dae::Renderer::GetInstance().GetSDLRenderer(), &m_Collider);
	}
	
}
