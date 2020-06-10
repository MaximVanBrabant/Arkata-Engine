#pragma once
#include "Component.h"
namespace dae
{
	class SelfDestructComponent : public Component
	{
	public:
		SelfDestructComponent(float time);
		void Initialize() override {}
		void Render() const override {}
		void Update(float deltaTime) override;
	private:
		float m_TimeToDestruct;
		float m_CurrentTime;
	};
}