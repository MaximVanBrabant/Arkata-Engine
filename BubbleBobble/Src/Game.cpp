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

	auto& scene = SceneManager::GetInstance().CreateScene("Demo00");

	//add textures
	ResourceManager::GetInstance().AddTexture("clockworker", "./RESIZE/dino.png");
	ResourceManager::GetInstance().AddTexture("apple", "/RESIZE/apple.png");

	//gameobject
	//!!!! think about move semantics / copyping
	std::shared_ptr<GameObject> apple = std::make_shared<GameObject>("apple");
	apple->AddComponent<Transform>(30, 20, 50, 50, 32, 32, 1);
	apple->AddComponent<SpriteComponent>("apple");
	scene.Add(apple);

	std::shared_ptr<GameObject> clockWorker = std::make_shared<GameObject>("clockWorker");
	clockWorker->AddComponent<Transform>(320, 240, -50, 0, 32, 32, 1);
	auto &sprite = clockWorker->AddComponent<SpriteComponent>("clockworker","idle", 2, 200, false);
	sprite.AddAnimation("moving", 1, 2, 200);
	sprite.Play("moving");
	sprite.AddAnimation("jumping", 3, 1, 100);
	sprite.Play("jumping");
	scene.Add(clockWorker);

	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>("hello");
	//auto& transformComponent = gameObject->AddComponent<Transform>(0,0,20,20,50,50,1);
	//scene.Add(gameObject);
	//std::cout << "name of the gameObject: " << transformComponent.m_Owner->GetName() << std::endl;


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
}

void Game::InitializeLevel03()
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");
}