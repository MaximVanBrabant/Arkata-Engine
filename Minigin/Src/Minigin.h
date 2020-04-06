#pragma once
struct SDL_Window;
#include "TextComponent.h"

namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() ;
		void Cleanup();
		void Run();
	private:
		float m_DeltaTime;
		int m_TicksPrevFrame;

		static const int DESIRED_FPS = 60;
		static const int MS_PER_SECOND = 1000;

		std::shared_ptr<TextComponent> pFrameCounter;
		SDL_Window* m_Window{};

	};
}