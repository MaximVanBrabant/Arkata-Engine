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

		std::shared_ptr<TextComponent> pFrameCounter;
		SDL_Window* m_Window{};

	};
}