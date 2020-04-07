#include "MiniginPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"

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

	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>("hello");
	auto& transformComponent = gameObject->AddComponent<Transform>(0,0,20,20,50,50,1);
	scene.Add(gameObject);
	std::cout << "name of the gameObject: " << transformComponent.GetGameObject()->GetName() << std::endl;


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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo00");

	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>("Projectile00");
	gameObject->AddComponent<Transform>(30, 20, 50, 80, 20, 100, 1);
	//sprite
	auto& spriteComponent = gameObject->AddComponent<SpriteComponent>();
	spriteComponent.AddTexture("./RESIZE/apple.png");
	scene.Add(gameObject);
	gameObject->ListComponents();


	gameObject = std::make_shared<GameObject>("Projectile01");
	gameObject->AddComponent<Transform>(500, 500, -50, -80, 200, 100, 1);
	scene.Add(gameObject);
	gameObject->ListComponents();

	gameObject = std::make_shared<GameObject>("Projectile02");
	gameObject->AddComponent<Transform>(0, 500, 50, -80, 25, 90, 1);
	scene.Add(gameObject);
	gameObject->ListComponents();

	gameObject = std::make_shared<GameObject>("Projectile03");
	gameObject->AddComponent<Transform>(500, 0, -100, 100, 50, 50, 1);
	scene.Add(gameObject);
	gameObject->ListComponents();

	SceneManager::GetInstance().SetActiveScene(scene.GetId());
}

void Game::InitializeLevel03()
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");
}