#pragma once
#include "Component.h"
#include <SDL_rect.h>
namespace dae
{
	class Transform;
	class ColliderComponent : public Component
	{
	public:
		ColliderComponent() = default;
		ColliderComponent(const std::string& tag);
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() const override;
		const SDL_Rect& GetCollider() const { return m_Collider; }
		const std::string& GetTag() const { return m_Tag; }

	private:
		//SDL_Rect m_CollisionBox;
		Transform* m_pTransform = nullptr;
		std::string m_Tag;
		SDL_Rect m_Collider;
	};
}
