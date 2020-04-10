#pragma once
#include "Component.h"
#include <SDL_rect.h>
namespace dae
{
	class Transform;
	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(const unsigned int screenWidth, const unsigned screenHeight);
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() const override;
	private:
		const unsigned int m_ScreenWidth;
		const unsigned int m_ScreenHeight;
		//SDL_Rect m_CollisionBox;
		Transform* m_pTransform;
		float m_xPos;
		float m_yPos;
	};
}
