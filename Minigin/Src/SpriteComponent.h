#pragma once
#include <string>
#include <map>
#include "SDL_rect.h"
#include "Texture2D.h"
#include "Animation.h"

namespace dae
{
	class Component;
	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(const std::string& textureId);
		SpriteComponent(const std::string& textureId,const std::string& animationId, unsigned int numFrames, unsigned int animationSpeed, bool isStatic);
		void Initialize() override;
		void Render() const override;
		void Update(float deltaTime) override;
		int AddTexture(const std::string& textureId);
		std::shared_ptr<Texture2D> GetTexture(int id) const;

		//animation on the same sprite
		void AddAnimation(const std::string& animationId,unsigned int index, unsigned int numFrames, unsigned int animationSpeed);
		void Play(const std::string& animationName);
	private:
		//pointer to the transform of the object because with a shared smart pointer it would copy the object because of the dynamic cast and so I would have a pointer to a new object
		Transform* m_pTransform;
		std::vector<std::shared_ptr<Texture2D>> m_pTextures{};
		SDL_Rect m_DestRect;
		SDL_Rect m_SrcRect;

		bool m_IsStatic;

		//Animations
		unsigned int m_NumFrames;
		bool m_IsAnimated;
		unsigned int m_AnimationSpeed;
		std::map<std::string, Animation> m_Animations;
		std::string m_CurAnimationName;
		std::string m_PrevAnimationName;
		unsigned int m_AnimationIndex;

	};
}

