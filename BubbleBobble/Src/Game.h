#pragma once
#include <string>


namespace dae
{
	class Game
	{
	public:
		Game();
		~Game() = default;
	private:
		void InitializeLevel01();
		void InitializeLevel02();
		void InitializeLevel03();
		void InitializeLevel04();

	};
}

