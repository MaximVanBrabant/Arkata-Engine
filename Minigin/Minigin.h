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
		static const int DESIRED_FPS = 60;
		static const int MS_PER_SECOND = 1000; //how much milliseconds are in one second
		std::shared_ptr<TextComponent> pFrameCounter;
		SDL_Window* m_Window{};
	};
}