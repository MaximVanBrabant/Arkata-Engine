#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h"
#include <SDL.h>

using namespace dae;

dae::SpriteComponent::SpriteComponent(const std::string& textureId)
	:m_DestRect{}, m_SrcRect{}, m_pTransform{nullptr},m_IsStatic{false},m_IsAnimated{false}
{
	m_pTextures.push_back(ResourceManager::GetInstance().GetTexture(textureId));
}

dae::SpriteComponent::SpriteComponent(const std::string& textureId, const std::string& animationId, unsigned int numFrames, unsigned int animationSpeed, bool isStatic)
	:m_IsAnimated{true}, m_NumFrames{numFrames}, m_AnimationSpeed{animationSpeed}, m_IsStatic{isStatic}
{
		Animation singleAnimation = Animation(0, numFrames, animationSpeed);
		m_Animations.emplace(animationId, singleAnimation);
		m_CurAnimationName = animationId;

	Play(m_CurAnimationName);
	m_pTextures.push_back(ResourceManager::GetInstance().GetTexture(textureId));
}

void dae::SpriteComponent::AddAnimation(const std::string& animationId,unsigned int index, unsigned int numFrames, unsigned int animationSpeed)
{
	Animation newAnimation = Animation(index, numFrames, animationSpeed);
	m_Animations.emplace(animationId, newAnimation);
}

void dae::SpriteComponent::Play(const std::string& animationName)
{
	m_NumFrames = m_Animations[animationName].m_NumFrames;
	m_AnimationIndex = m_Animations[animationName].m_Index;
	m_AnimationSpeed = m_Animations[animationName].m_AnimationSpeed;
	m_CurAnimationName = animationName;
}

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
		Renderer::GetInstance().RenderTexture(*x, m_DestRect, m_SrcRect);
	}
}

void dae::SpriteComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_IsAnimated)
	{
		//modulus makes the result always smaller than numFames -> getTicks always changes
		m_SrcRect.x = m_SrcRect.w * static_cast<int>((SDL_GetTicks() / m_AnimationSpeed) % m_NumFrames);
		m_SrcRect.y = m_AnimationIndex * m_pTransform->GetHeight();
	}


	m_DestRect.x = static_cast<int>( m_pTransform->GetPosition().x);
	m_DestRect.y = static_cast<int>(m_pTransform->GetPosition().y);
	m_DestRect.w = m_pTransform->GetWidth() * m_pTransform->GetScale();
	m_DestRect.h = m_pTransform->GetHeight() * m_pTransform->GetScale();
}

int SpriteComponent::AddTexture(const std::string& textureId)
{
	int id = (int)m_pTextures.size();
	m_pTextures.push_back(ResourceManager::GetInstance().GetTexture(textureId));

	return id;
}

void dae::SpriteComponent::RemoveTexture(int textureIndex)
{
	m_pTextures[textureIndex] = m_pTextures[m_pTextures.size() - 1];
	m_pTextures.pop_back();
}

std::shared_ptr<Texture2D> SpriteComponent::GetTexture(int id) const
{
	return m_pTextures[id];
}