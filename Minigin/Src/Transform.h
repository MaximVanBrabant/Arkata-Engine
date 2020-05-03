#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

#include "Component.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		//width and height is also what the srcRect will use / destRect = width * scale
		Transform(int posX, int posY, int velX, int velY, int w, int h, int s);
		const glm::vec2& GetPosition() const { return m_Position; }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
		int GetScale() const { return m_Scale; }

		void ApplyForceToVelocity(float x, float y);
		void SetPosition(float x, float y);
		void SetVelocity(float x, float y);
		const glm::vec2& GetVelocity() const { return m_Velocity; }

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() const override;
	private:
		glm::vec2 m_Position;
		glm::vec2 m_Velocity;
		int m_Width;
		int m_Height;
		int m_Scale;
	};
}
