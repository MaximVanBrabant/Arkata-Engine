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
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	////gameObject->AddRenderComponent(std::make_shared<RenderComponent>());
	////gameObject->GetRenderComponent()->AddTexture("background.jpg");
	////int idLogo = gameObject->GetRenderComponent()->AddTexture("logo.png");
	////gameObject->GetRenderComponent()->SetPositionTexture(idLogo, 216, 180, 0);
	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	////gameObject->AddTextComponent("Programming 4 Assignment", font);
	////gameObject->GetTextComponent()->SetPosition(80, 20);
	////scene.Add(gameObject);

	////change the content of gameObject to a new pointer that points to a different gameobject with no components yet
	//gameObject = std::make_shared<GameObject>();
	//gameObject->AddTextComponent("0",font);
	//pFrameCounter = gameObject->GetTextComponent();
	//scene.Add(gameObject);

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

	//dont constantly update the framecounter
	//const float cooldownTime{ 0.25f };
	//float accumulatedTime{};
	//Uint32 fps{};
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

			//clamp -> slow computers -> minimum 20 fps -> no idea why i do this
			m_DeltaTime = (m_DeltaTime > 0.05f) ? 0.05f : m_DeltaTime;
			//FPS COUNTER
			//std::cout << 1/m_DeltaTime << std::endl;

			//if (accumulatedTime > cooldownTime)
			//{
			//	if (m_DeltaTime != 0)
			//		fps = Uint32(1 / m_DeltaTime);
			//	pFrameCounter->SetText(std::to_string(fps));
			//	accumulatedTime = 0;
			//}

			doContinue = input.ProcessInput();

			sceneManager.Update(m_DeltaTime);

			renderer.Render();
			
			//accumulatedTime += m_DeltaTime;


			//using int here so it doesn't implicitly convert it to an unsigned int / this value can be negative if your computer runs slow


		}
	}

	Cleanup();
}
