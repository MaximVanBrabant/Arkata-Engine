#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"

using namespace dae;

void RenderComponent::Render(Transform transform) const
{
	for (std::shared_ptr<Texture2D> x : m_pTextures)
	{
		const auto pos = transform.GetPosition() + x->GetTranform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*x, pos.x, pos.y);
	}
}
 
int RenderComponent::AddTexture(const std::string& filename)
{
	int id = (int)m_pTextures.size();
	m_pTextures.push_back(ResourceManager::GetInstance().LoadTexture(filename));

	return id;
}

std::shared_ptr<Texture2D> RenderComponent::GetTexture(int id) const
{
	return m_pTextures[id];
}

void RenderComponent::SetPositionTexture(int id, float x, float y, float z)
{
	m_pTextures[id]->GetTranform()->SetPosition(x, y, z);
}