#pragma once
#include "Component.h"
namespace dae
{
	class Transform;
	class RigidBodyComponent : public Component
	{
	public:
		RigidBodyComponent() = default;
		void Initialize() override;
		void Update(float deltaTime) override;
		void EnableGravity(bool enable) { m_GravityOn = enable; }

	private:
		Transform* m_pTransform = nullptr;
		//gravity positive because Y-value goind downwards is getting higher in SDL framework
		bool m_GravityOn = true;
		const float m_Gravity = 250.0f;
	};
}

