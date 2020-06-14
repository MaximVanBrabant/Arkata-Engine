#include "MiniginPCH.h"
#include "EntityCounter.h"
#include "GameObject.h"

dae::EntityCounter::~EntityCounter()
{
	for (Observer* o : m_vpObservers)
	{
		if (o != nullptr)
		{
			delete o;
		}
	}
}

void dae::EntityCounter::Register(Observer* o)
{
	m_vpObservers.push_back(o);
}

void dae::EntityCounter::Unregister(Observer* o)
{
	int index{ 0 };

	for (Observer* observer : m_vpObservers)
	{
		if (o == observer)
		{
			m_vpObservers[index] = m_vpObservers[m_vpObservers.size() - 1];
			m_vpObservers.pop_back();
			return;
		}
		++index;
	}
}

void dae::EntityCounter::NotifyObserver()
{
	for (Observer* observer : m_vpObservers)
	{
		observer->Update(m_EnemiesAlive, m_ScorePlayer1, m_ScorePlayer2, m_HealthPlayer1, m_HealthPlayer2);
	}
}

void dae::EntityCounter::EnemyKilled()
{
	--m_EnemiesAlive;
	NotifyObserver();
}

void dae::EntityCounter::ScoreIncrementation(int score, int playerIndex)
{
	if (playerIndex == 1)
	{
		m_ScorePlayer1 += score;
	}
	else if (playerIndex == 2)
	{
		m_ScorePlayer2 += score;
	}

	NotifyObserver();
}

void dae::EntityCounter::HealthDecrementation(int amount, int playerIndex, const std::shared_ptr<GameObject>& playerObject)
{
	if (playerIndex == 1)
	{
		m_HealthPlayer1 -= amount;
		if (m_HealthPlayer1 == 0)
		{
			playerObject->Destroy();
		}
	}
	else if (playerIndex == 2)
	{
		m_HealthPlayer2 -= amount;
		if (m_HealthPlayer2 == 0)
		{
			playerObject->Destroy();
		}
	}

	NotifyObserver();
}

void dae::EntityCounter::InitializeObserversInNewScene()
{
	for (auto o : m_vpObservers)
	{
		o->InitializeInNewScene();
	}
}
