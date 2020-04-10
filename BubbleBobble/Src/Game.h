#pragma once
#include <string>


namespace dae
{
	class Game
	{
	public:
		Game(const unsigned int screenWidth, const unsigned int screenHeight);
		~Game() = default;
		void InitializeLevel01();
		void InitializeLevel02();
		void InitializeLevel03();
	private:
		const unsigned int m_ScreenWidth;
		const unsigned int m_ScreenHeight;

	};
}

