#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"

using namespace dae;

void dae::SpriteComponent::Initialize()
{
	m_pTransform = m_Owner->GetComponent<Transform>();
	m_SrcRect.x = 0;
	m_SrcRect.y = 0;
	m_SrcRect.w = m_pTransform->GetWidth();
	m_SrcRect.h = m_pTransform->GetHeight();
}

void SpriteComponent::Render() const
{
	for (std::shared_ptr<Texture2D> x : m_pTextures)
	{
		//const auto pos = m_pTransform->GetPosition();
		//Renderer::GetInstance().RenderTexture(*x, pos.x, pos.y);
		Renderer::GetInstance().RenderTexture(*x, m_DestRect, m_SrcRect);
	}
}

void dae::SpriteComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_DestRect.x = (int) m_pTransform->GetPosition().x;
	m_DestRect.y = (int) m_pTransform->GetPosition().y;
	m_DestRect.w = m_pTransform->GetWidth() * m_pTransform->GetScale();
	m_DestRect.h = m_pTransform->GetHeight() * m_pTransform->GetScale();
}

int SpriteComponent::AddTexture(const std::string& filename)
{
	int id = (int)m_pTextures.size();
	m_pTextures.push_back(ResourceManager::GetInstance().LoadTexture(filename));

	return id;
}

std::shared_ptr<Texture2D> SpriteComponent::GetTexture(int id) const
{
	return m_pTextures[id];
}

//void SpriteComponent::SetPositionTexture(int id, float x, float y)
//{
//	//m_pTextures[id]->GetTranform()->SetPosition(x, y);
//}