#pragma once
#include "Component.h"
namespace dae
{
	class Transform;
	class BellComponent : public Component
	{
	public:
		BellComponent();
		void Initialize() override;
		void Render() const override {}
		void Update(float deltaTime) override;
	private:
		const float m_DecreasingSpeed = 100.f;
		const float m_RisingVelocity = 100.f;
		bool m_RisingPhase;
		Transform* m_pTransform;
	};
}