#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include <algorithm>
#include "Game.h"
#include "Constants.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	//zeroInitiliaze
	m_TicksPrevFrame = 0;
	m_DeltaTime = 0.0f;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOWWIDTH,
		WINDOWHEIGHT,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() 
{
	std::cout << "First player uses the arrow keys + space to move / jump / shoot" << std::endl;
	std::cout << "press enter to spawn the second player " << std::endl;
	std::cout << "second player uses WASD to move / jump / shoot" << std::endl;

	std::cout << std::endl << std::endl << "last level is the versus mode between player(s) and the maita" << std::endl;
	std::cout << "the maita is controlled by the T / F / H / G keys " << std::endl;
	Game game{};
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("./Data/");

	LoadGame();
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			int delayTime = TIME_PER_FRAME - (SDL_GetTicks() - m_TicksPrevFrame);

			if (delayTime > 0)
				SDL_Delay(delayTime);
			
			//start gameLoop
			m_DeltaTime = (SDL_GetTicks() - m_TicksPrevFrame) / 1000.f;
			m_TicksPrevFrame = SDL_GetTicks();

			m_DeltaTime = (m_DeltaTime > 0.05f) ? 0.05f : m_DeltaTime;
			//FPS COUNTER
			//std::cout << 1/m_DeltaTime << std::endl;

			doContinue = input.ProcessInput();

			sceneManager.Update(m_DeltaTime);

			renderer.Render();
		}
	}

	Cleanup();
}
