#pragma once
#include "MiniginPCH.h"
#include "Component.h"
namespace dae
{

	class PlayerComponent : public Component
	{
	public:
		PlayerComponent(int playerID) : m_PlayerID{playerID} {}
		void Initialize() override {};
		void Render() const override {}
		void Update(float deltaTime) override { UNREFERENCED_PARAMETER(deltaTime); }
		int GetPlayerID() const { return m_PlayerID; }
	private:
		int m_PlayerID = 0;
	};
}