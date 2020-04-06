#include "MiniginPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"

using namespace dae;

Game::Game()
{
	InitializeLevel01();
	InitializeLevel02();
	InitializeLevel03();
}

void Game::InitializeLevel01()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	gameObject->AddComponent<Transform>(0,0,20,20,50,50,1);
	scene.Add(gameObject);



	//gameObject->AddRenderComponent(std::make_shared<RenderComponent>());
	//gameObject->GetRenderComponent()->AddTexture("background.jpg");
	//int idLogo = gameObject->GetRenderComponent()->AddTexture("logo.png");
	//gameObject->GetRenderComponent()->SetPositionTexture(idLogo, 216, 180, 0);
	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//gameObject->AddTextComponent("Programming 4 Assignment", font);
	//gameObject->GetTextComponent()->SetPosition(80, 20);
	//scene.Add(gameObject);

	//change the content of gameObject to a new pointer that points to a different gameobject with no components yet
	//gameObject = std::make_shared<GameObject>();
	//gameObject->AddTextComponent("0", font);
	//pFrameCounter = gameObject->GetTextComponent();
	//scene.Add(gameObject);
}

void Game::InitializeLevel02()
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo00");

	//std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	//scene.Add(gameObject);

	//SceneManager::GetInstance().SetActiveScene(scene.GetId());
}

void Game::InitializeLevel03()
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");
}