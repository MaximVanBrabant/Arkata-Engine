#pragma once
#include "SDL_rect.h"
#include "Texture2D.h"

namespace dae
{
	class Component;
	class SpriteComponent : public Component
	{
	public:
		SpriteComponent() = default;
		void Initialize() override;
		void Render() const override;
		void Update(float deltaTime) override;
		int AddTexture(const std::string& filename);
		std::shared_ptr<Texture2D> GetTexture(int id) const;
	private:
		std::vector<std::shared_ptr<Texture2D>> m_pTextures{};
		SDL_Rect m_DestRect;
		SDL_Rect m_SrcRect;
		//pointer to the transform of the object because with a shared smart pointer it would copy the object because of the dynamic cast and so I would have a pointer to a new object
		Transform* m_pTransform;
	};
}

