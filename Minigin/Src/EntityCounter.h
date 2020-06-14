#pragma once
#include "Subject.h"
#include "GameObject.h"
#include <vector>
namespace dae
{
	class EntityCounter : public Subject
	{
	public:
		EntityCounter() = default;
		virtual ~EntityCounter();
		void Register(Observer* o) override;
		void Unregister(Observer* o) override;
		void NotifyObserver() override;


		
		void EnemyKilled();
		void ScoreIncrementation(int score, int playerIndex);
		void HealthDecrementation(int amount, int playerIndex,const std::shared_ptr<GameObject>& playerObject);

		void SetEnemiesAlive(int enemiesAlive) { m_EnemiesAlive = enemiesAlive; }

		void InitializeObserversInNewScene();
	private:
		std::vector<Observer*> m_vpObservers;

		int m_EnemiesAlive = 0;

		int m_ScorePlayer1 = 0;
		int m_ScorePlayer2 = 0;

		int m_HealthPlayer1 = 4;
		int m_HealthPlayer2 = 4;

	};


}