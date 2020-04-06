#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"

using namespace dae;

void SpriteComponent::Render() const
{
	for (std::shared_ptr<Texture2D> x : m_pTextures)
	{
		//const auto pos = transform.GetPosition() + x->GetTranform()->GetPosition();
		//Renderer::GetInstance().RenderTexture(*x, pos.x, pos.y);
	}
}

void dae::SpriteComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
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