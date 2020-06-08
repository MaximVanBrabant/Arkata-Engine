#include "MiniginPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "KeyboardInputComponent.h"
#include "ColliderComponent.h"
#include "TileComponent.h"
#include "RigidBodyComponent.h"
#include "Level.h"
#include "PlayerSM.h"
#include "EnemySM.h"

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
	ResourceManager::GetInstance().AddTexture("dino", "./RESIZE/dino.png");
	ResourceManager::GetInstance().AddTexture("apple", "/RESIZE/apple.png");
	ResourceManager::GetInstance().AddTexture("clockworker", "/RESIZE/clockworker.png");
	ResourceManager::GetInstance().AddTexture("tiles", "/RESIZE/tiles.png");
	ResourceManager::GetInstance().AddTexture("bullet", "/RESIZE/bullets.png");
	ResourceManager::GetInstance().AddTexture("bubble", "/RESIZE/bubbles.png");

	std::shared_ptr<Level> pLevel = std::make_shared<Level>("tiles", 1,32, scene);
	pLevel->LoadMap("./Data/RESIZE/level.map", 20, 15);

	//gameobject
	//!!!! think about move semantics / copyping
	//std::shared_ptr<GameObject> apple = std::make_shared<GameObject>("apple", false);
	//apple->AddComponent<Transform>(70, 20, 0, 0, 32, 32, 1);
	//apple->AddComponent<ColliderComponent>("ITEM");
	//apple->AddComponent<RigidBodyComponent>();
	//apple->AddComponent<SpriteComponent>("apple");
	//scene.Add(apple);

	std::shared_ptr<GameObject> dino = std::make_shared<GameObject>("dino", false);
	dino->AddComponent<Transform>(320, 240, 0, 0, 32, 32,1);
	dino->AddComponent<PlayerSM>();
	auto &sprite = dino->AddComponent<SpriteComponent>("dino","idle", 2, 200, false);
	dino->AddComponent<RigidBodyComponent>();
	dino->AddComponent<ColliderComponent>("PLAYER");
	dino->AddComponent<KeyboardInputComponent>("left", "right", "up", "space");
	sprite.AddAnimation("moving", 1, 2, 200);
	sprite.AddAnimation("jumping", 3, 1, 100);
	sprite.AddAnimation("shoot", 2, 1, 10);
	scene.Add(dino);

	std::shared_ptr<GameObject> clockworker = std::make_shared<GameObject>("clockworker", false);
	clockworker->AddComponent<Transform>(80, 200, 0, 0, 32, 32, 1);
	clockworker->AddComponent<SpriteComponent>("clockworker", "standard", 2,200, false);
	clockworker->AddComponent<RigidBodyComponent>();
	clockworker->AddComponent<ColliderComponent>("ENEMY");
	clockworker->AddComponent<EnemySM>(dino, EnemyType::Throw);
	scene.Add(clockworker);

	std::shared_ptr<GameObject> clockworker_1 = std::make_shared<GameObject>("clockworker_1", false);
	clockworker_1->AddComponent<Transform>(250, 200, 0, 0, 32, 32, 1);
	clockworker_1->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	clockworker_1->AddComponent<RigidBodyComponent>();
	clockworker_1->AddComponent<ColliderComponent>("ENEMY");
	clockworker_1->AddComponent<EnemySM>(dino, EnemyType::Charge);
	scene.Add(clockworker_1);


	std::shared_ptr<GameObject> clockworker_2 = std::make_shared<GameObject>("clockworker_2", false);
	clockworker_2->AddComponent<Transform>(400, 100, 0, 0, 32, 32, 1);
	clockworker_2->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	clockworker_2->AddComponent<RigidBodyComponent>();
	clockworker_2->AddComponent<ColliderComponent>("ENEMY");
	clockworker_2->AddComponent<EnemySM>(dino, EnemyType::Charge);
	scene.Add(clockworker_2);



	//std::shared_ptr<GameObject> clockworker_3 = std::make_shared<GameObject>("clockworker_3", false);
	//clockworker_3->AddComponent<Transform>(200, 150, 0, 0, 32, 32, 1);
	//clockworker_3->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	//clockworker_3->AddComponent<RigidBodyComponent>();
	//clockworker_3->AddComponent<ColliderComponent>("ENEMY");
	//clockworker_3->AddComponent<EnemySM>(dino, EnemyType::Charge);
	//scene.Add(clockworker_3);



	//std::shared_ptr<GameObject> clockworker_4 = std::make_shared<GameObject>("clockworker_4", false);
	//clockworker_4->AddComponent<Transform>(500, 250, 0, 0, 32, 32, 1);
	//clockworker_4->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	//clockworker_4->AddComponent<RigidBodyComponent>();
	//clockworker_4->AddComponent<ColliderComponent>("ENEMY");
	//clockworker_4->AddComponent<EnemySM>(dino, EnemyType::Charge);
	//scene.Add(clockworker_4);

	//std::shared_ptr<GameObject> clockworker_5 = std::make_shared<GameObject>("clockworker_5", false);
	//clockworker_5->AddComponent<Transform>(125, 300, 0, 0, 32, 32, 1);
	//clockworker_5->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	//clockworker_5->AddComponent<RigidBodyComponent>();
	//clockworker_5->AddComponent<ColliderComponent>("ENEMY");
	//clockworker_5->AddComponent<EnemySM>(dino, EnemyType::Throw);
	//scene.Add(clockworker_5);

	//std::shared_ptr<GameObject> dino1 = std::make_shared<GameObject>("dino1", false);
	//dino1->AddComponent<Transform>(420, 300, 0, 0, 32, 32, 1);
	//auto& sprite1 = dino1->AddComponent<SpriteComponent>("dino", "idle", 2, 200, false);
	////dino1->AddComponent<ColliderComponent>("PLAYER");
	//dino1->AddComponent<KeyboardInputComponent>("a", "d", "w", "s");
	//sprite1.AddAnimation("moving", 1, 2, 200);
	//sprite1.AddAnimation("jumping", 3, 1, 100);
	//sprite1.AddAnimation("shoot", 2, 1, 10);
	//scene.Add(dino1);


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