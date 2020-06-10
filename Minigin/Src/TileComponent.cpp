#include "MiniginPCH.h"
#include "TileComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::TileComponent::TileComponent(int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale, const std::string& textureId)
{
	m_pTexture = ResourceManager::GetInstance().GetTexture(textureId);
	m_SrcRect.x = srcRectX;
	m_SrcRect.y = srcRectY;
	m_SrcRect.w = tileSize;
	m_SrcRect.h = tileSize;

	m_DestRect.x = x;
	m_DestRect.y = y;
	m_DestRect.w = tileSize * tileScale;
	m_DestRect.h = tileSize * tileScale;
}


void dae::TileComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_DestRect, m_SrcRect);
}
