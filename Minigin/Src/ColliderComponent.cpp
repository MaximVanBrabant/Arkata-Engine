#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Transform.h"
#include "Renderer.h"
#include "GameObject.h"
#include <SDL.h>
dae::ColliderComponent::ColliderComponent(const unsigned int screenWidth, const unsigned screenHeight)
	:m_ScreenHeight{ screenHeight }, m_ScreenWidth{ screenWidth }, m_pTransform{ nullptr }, m_xPos{}, m_yPos{}//, m_CollisionBox{}
{
}
void dae::ColliderComponent::Initialize()
{
	m_pTransform = m_Owner->GetComponent<Transform>();
}

void dae::ColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_xPos = m_pTransform->GetPosition().x;
	m_yPos = m_pTransform->GetPosition().y;

	//m_CollisionBox.x = static_cast<int>(m_pTransform->GetPosition().x);
	//m_CollisionBox.y = static_cast<int>(m_pTransform->GetPosition().y);
	//m_CollisionBox.w = m_pTransform->GetWidth() * m_pTransform->GetScale();
	//m_CollisionBox.h = m_pTransform->GetHeight() * m_pTransform->GetScale();

	//check for collisions
	if (m_xPos < 0)
	{
		m_xPos = 0;
	}
	else if (m_xPos + m_pTransform->GetWidth() > static_cast<int>(m_ScreenWidth))
	{
		m_xPos = static_cast<float>(m_ScreenWidth - m_pTransform->GetWidth());
	}

	m_pTransform->SetPosition(m_xPos, m_yPos);
}

void dae::ColliderComponent::Render() const
{
	SDL_Rect transformRectangle = {static_cast<int>(m_xPos), static_cast<int>(m_yPos), m_pTransform->GetWidth() * m_pTransform->GetScale(), m_pTransform->GetHeight()};
	SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawRect(dae::Renderer::GetInstance().GetSDLRenderer(), &transformRectangle);
	
}
