#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

#include "Component.h"
#include <SDL_Rect.h>

namespace dae
{
	class Texture2D;
	class TileComponent : public Component
	{
	public:
		TileComponent(int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale, const std::string& textureId);
		~TileComponent() = default;
		void Render() const override;
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		SDL_Rect m_SrcRect;
		SDL_Rect m_DestRect;
	};
}

