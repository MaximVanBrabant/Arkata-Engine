#pragma once
namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Update(int enemiesAlive, int scorePlayer1, int scorePlayer2, int healthPlayer1, int healthPlayer2) = 0;
		virtual void InitializeInNewScene() = 0;
	};
}