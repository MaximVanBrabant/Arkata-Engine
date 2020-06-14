#pragma once
#include "MiniginPCH.h"
#include "Component.h"
namespace dae
{
	enum class FoodType
	{
		fries,
		melon
	};

	class FoodComponent : public Component
	{
	public:
		FoodComponent(FoodType foodtype) : m_FoodType{ foodtype } {}
		void Initialize() override {};
		void Render() const override {}
		void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); }
		FoodType GetFoodType() const { return m_FoodType; }
	private:
		FoodType m_FoodType;
	};
}