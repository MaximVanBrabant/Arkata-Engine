#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Transform.h"
#include "Renderer.h"
#include "GameObject.h"
#include <SDL.h>
#include "Constants.h"
#include "RigidBodyComponent.h"
dae::ColliderComponent::ColliderComponent(const std::string& tag)
	:m_pTransform{ nullptr }, m_Collider{}, m_Tag{tag}
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

	m_Collider.x = static_cast<int>(m_pTransform->GetPosition().x);
	m_Collider.y = static_cast<int>(m_pTransform->GetPosition().y);
	m_Collider.w = m_pTransform->GetWidth() * m_pTransform->GetScale();
	m_Collider.h = m_pTransform->GetHeight() * m_pTransform->GetScale();

	m_CenterX = m_Collider.x + m_Collider.w / 2.0f;
	m_CenterY = m_Collider.y + m_Collider.h / 2.0f;

	//check for collisions
	if (m_Collider.x < 0)
	{
		m_Collider.x = 0;
	}
	else if (m_Collider.x + m_pTransform->GetWidth() > WINDOWWIDTH)
	{
		m_Collider.x = WINDOWWIDTH - m_pTransform->GetWidth();
	}

	if (m_Collider.y < 0)
	{
		m_Collider.y = 0;
	}
	else if (m_Collider.y + m_pTransform->GetHeight() > WINDOWHEIGHT)
	{
		m_Collider.y = WINDOWHEIGHT - m_pTransform->GetHeight();

		//just for testing move this code to somehwere else ->

		m_pTransform->SetVelocity(m_pTransform->GetVelocity().x, 0);
	}

	m_pTransform->SetPosition(static_cast<float>(m_Collider.x), static_cast<float>(m_Collider.y));
}

void dae::ColliderComponent::Render() const
{
	SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawRect(dae::Renderer::GetInstance().GetSDLRenderer(), &m_Collider);
	
}
