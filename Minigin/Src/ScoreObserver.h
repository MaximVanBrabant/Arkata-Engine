#pragma once
#include "Subject.h"
#include "Observer.h"
#include "GameObject.h"
#include <memory>
namespace dae
{
	class ScoreObserver : public Observer
	{
	public:
		ScoreObserver(Subject* entityCounter, const glm::vec2& position);
		void Update(int enemiesAlive, int scorePlayer1, int scorePlayer2, int healthPlayer1, int healthPlayer2) override;

		void InitializeInNewScene() override;
	private:
		Subject* m_EntityCounter;

		std::shared_ptr<GameObject> m_ScorePlayer;
		std::shared_ptr<GameObject> m_HealthPlayer;
		int m_PlayerID;
		static int m_AmountOfPlayers;

		const int m_Offset = 50;
		const int m_FontSize = 20;
	};

}