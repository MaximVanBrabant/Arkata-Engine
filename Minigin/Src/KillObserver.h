#pragma once
#include "Subject.h"
#include "Observer.h"
namespace dae
{
	class KillObserver : public Observer
	{
	public:
		KillObserver(Subject* entityCounter) :m_EntityCounter{ entityCounter } { entityCounter->Register(this); }
		void Update(int enemiesAlive, int scorePlayer1, int scorePlayer2, int playerHealth1, int playerHealth2) override;
		void InitializeInNewScene() override {}
	private:
		Subject* m_EntityCounter;
	};

}