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
		Transform(int posX, int posY, int velX, int velY, int w, int h, int s);
		const glm::vec2& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y);

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
