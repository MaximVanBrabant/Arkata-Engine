#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "RenderComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include <algorithm>

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	gameObject->AddRenderComponent(std::make_shared<RenderComponent>());
	gameObject->GetRenderComponent()->AddTexture("background.jpg");
	int idLogo = gameObject->GetRenderComponent()->AddTexture("logo.png");
	gameObject->GetRenderComponent()->SetPositionTexture(idLogo, 216, 180, 0);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	gameObject->AddTextComponent("Programming 4 Assignment", font);
	gameObject->GetTextComponent()->SetPosition(80, 20);
	scene.Add(gameObject);

	//change the content of gameObject to a new pointer that points to a different gameobject with no components yet
	gameObject = std::make_shared<GameObject>();
	gameObject->AddTextComponent("0",font);
	pFrameCounter = gameObject->GetTextComponent();
	scene.Add(gameObject);
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
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	const Uint32 DESIRED_FRAMERATE{ MS_PER_SECOND / DESIRED_FPS };

	//set current time
	Uint32 lastTime = SDL_GetTicks();
	//dont constantly update the framecounter
	const Uint32 cooldownTime{ MS_PER_SECOND / 4 };
	Uint32 accumulatedTime{};
	Uint32 fps{};
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			//start gameLoop
			Uint32 startTime = SDL_GetTicks();
			Uint32 elapsedTime = startTime - lastTime;

			if (accumulatedTime > cooldownTime)
			{
				if (elapsedTime != 0)
					fps = MS_PER_SECOND / elapsedTime;
				pFrameCounter->SetText(std::to_string(fps));
				accumulatedTime = 0;
			}

			doContinue = input.ProcessInput();

			sceneManager.Update(float(elapsedTime));
			renderer.Render();
			
			//end gameLoop
			lastTime = startTime;
			accumulatedTime += elapsedTime;


			Uint32 endTime = SDL_GetTicks();
			//using int here so it doesn't implicitly convert it to an unsigned int / this value can be negative if your computer runs slow
			int delayTime = lastTime + DESIRED_FRAMERATE - endTime;

			if (delayTime > 0)
				SDL_Delay(delayTime);

		}
	}

	Cleanup();
}
