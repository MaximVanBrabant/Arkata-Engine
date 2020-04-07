#include "MiniginPCH.h"
#include "SDL.h"
#include "Transform.h"
#include "Renderer.h"

dae::Transform::Transform(int posX, int posY, int velX, int velY, int w, int h, int s)
	:m_Position{ glm::vec2{posX, posY} }
	, m_Velocity{ glm::vec2{velX, velY} }
	,m_Width{w}
	,m_Height{h}
	,m_Scale{s}

{
}

void dae::Transform::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void dae::Transform::Initialize()
{
}

void dae::Transform::Update(float deltaTime)
{
	//update the position / velocity
	m_Position.x += m_Velocity.x * deltaTime;
	m_Position.y += m_Velocity.y * deltaTime;
}

void dae::Transform::Render() const 
{
	//SDL_Rect transformRectangle = {(int)m_Position.x, (int)m_Position.y, m_Width, m_Height};
	//SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 255);
	//SDL_RenderFillRect(dae::Renderer::GetInstance().GetSDLRenderer(), &transformRectangle);
}
