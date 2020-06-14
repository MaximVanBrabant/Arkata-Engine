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
#include "EntityCounter.h"
#include "KillObserver.h"
#include "TextComponent.h"
#include "ScoreObserver.h"
#include "PlayerComponent.h"
#include "Constants.h"

using namespace dae;

Game::Game()
{
	InitializeLevel01();
	InitializeLevel02();
	InitializeLevel03();
}

void Game::InitializeLevel01()
{

	auto& scene = SceneManager::GetInstance().CreateScene("LEVEL_0");

	//add textures
	ResourceManager::GetInstance().AddTexture("dino", "./RESIZE/dino.png");
	ResourceManager::GetInstance().AddTexture("dino_00", "./RESIZE/dino_00.png");
	ResourceManager::GetInstance().AddTexture("maita", "./RESIZE/maita.png");
	ResourceManager::GetInstance().AddTexture("clockworker", "/RESIZE/clockworker.png");
	ResourceManager::GetInstance().AddTexture("tiles", "/RESIZE/tiles.png");
	ResourceManager::GetInstance().AddTexture("bullet", "/RESIZE/bullets.png");
	ResourceManager::GetInstance().AddTexture("bubble", "/RESIZE/bubbles.png");
	ResourceManager::GetInstance().AddTexture("fries", "/RESIZE/fries.png");
	ResourceManager::GetInstance().AddTexture("melon", "/RESIZE/melon.png");

	//SUBJECT
	SceneManager::GetInstance().GetEntityCounter()->SetEnemiesAlive(4);

	//OBSERVER
	KillObserver* killObserver{ new KillObserver{SceneManager::GetInstance().GetEntityCounter()} };
	UNREFERENCED_PARAMETER(killObserver);

	std::shared_ptr<Level> pLevel = std::make_shared<Level>("tiles", 1,32, scene);
	pLevel->LoadMap("./Data/RESIZE/level.map", 20, 15);

	std::shared_ptr<GameObject> dino = std::make_shared<GameObject>("dino", false);
	dino->AddComponent<Transform>(320, 240, 0, 0, 32, 32,1);
	dino->AddComponent<PlayerSM>();
	dino->AddComponent<PlayerComponent>(1);
	auto &sprite = dino->AddComponent<SpriteComponent>("dino","idle_right", 2, 200, false);
	dino->AddComponent<RigidBodyComponent>();
	dino->AddComponent<ColliderComponent>("PLAYER");
	dino->AddComponent<KeyboardInputComponent>("left", "right", "up", "space");
	sprite.AddAnimation("moving_right", 1, 2, 200);
	sprite.AddAnimation("shoot_right", 2, 1, 10);
	sprite.AddAnimation("jumping_right", 3, 1, 100);
	sprite.AddAnimation("idle_left", 4, 2, 200);
	sprite.AddAnimation("moving_left", 5, 2, 200);
	sprite.AddAnimation("shoot_left", 6, 1, 10);
	sprite.AddAnimation("jumping_left", 7, 1, 100);
	scene.Add(dino);

	//std::shared_ptr<GameObject> dino_01 = std::make_shared<GameObject>("dino_01", false);
	//dino_01->AddComponent<Transform>(300, 240, 0, 0, 32, 32, 1);
	//dino_01->AddComponent<PlayerSM>();
	//dino_01->AddComponent<PlayerComponent>(2);
	//auto& sprite_01 = dino_01->AddComponent<SpriteComponent>("dino_00", "idle_right", 2, 200, false);
	//dino_01->AddComponent<RigidBodyComponent>();
	//dino_01->AddComponent<ColliderComponent>("PLAYER");
	//dino_01->AddComponent<KeyboardInputComponent>("a", "d", "w", "s");
	//sprite_01.AddAnimation("moving_right", 1, 2, 200);
	//sprite_01.AddAnimation("shoot_right", 2, 1, 10);
	//sprite_01.AddAnimation("jumping_right", 3, 1, 100);
	//sprite_01.AddAnimation("idle_left", 4, 2, 200);
	//sprite_01.AddAnimation("moving_left", 5, 2, 200);
	//sprite_01.AddAnimation("shoot_left", 6, 1, 10);
	//sprite_01.AddAnimation("jumping_left", 7, 1, 100);
	//scene.Add(dino_01);

	std::shared_ptr<GameObject> clockworker = std::make_shared<GameObject>("clockworker", false);
	clockworker->AddComponent<Transform>(80, 200, 0, 0, 32, 32, 1);
	clockworker->AddComponent<SpriteComponent>("maita", "standard", 2,200, false);
	clockworker->AddComponent<RigidBodyComponent>();
	clockworker->AddComponent<ColliderComponent>("ENEMY");
	clockworker->AddComponent<EnemySM>(dino, EnemyType::Throw);
	scene.Add(clockworker);

	std::shared_ptr<GameObject> clockworker_1 = std::make_shared<GameObject>("clockworker_1", false);
	clockworker_1->AddComponent<Transform>(250, 200, 0, 0, 32, 32, 1);
	clockworker_1->AddComponent<SpriteComponent>("maita", "standard", 2, 200, false);
	clockworker_1->AddComponent<RigidBodyComponent>();
	clockworker_1->AddComponent<ColliderComponent>("ENEMY");
	clockworker_1->AddComponent<EnemySM>(dino, EnemyType::Throw);
	scene.Add(clockworker_1);


	std::shared_ptr<GameObject> clockworker_2 = std::make_shared<GameObject>("clockworker_2", false);
	clockworker_2->AddComponent<Transform>(400, 100, 0, 0, 32, 32, 1);
	clockworker_2->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	clockworker_2->AddComponent<RigidBodyComponent>();
	clockworker_2->AddComponent<ColliderComponent>("ENEMY");
	clockworker_2->AddComponent<EnemySM>(dino, EnemyType::Charge);
	scene.Add(clockworker_2);

	std::shared_ptr<GameObject> clockworker_3 = std::make_shared<GameObject>("clockworker_3", false);
	clockworker_3->AddComponent<Transform>(250, 450, 0, 0, 32, 32, 1);
	clockworker_3->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	clockworker_3->AddComponent<RigidBodyComponent>();
	clockworker_3->AddComponent<ColliderComponent>("ENEMY");
	clockworker_3->AddComponent<EnemySM>(dino, EnemyType::Charge);
	scene.Add(clockworker_3);


	Observer* scoreObserver{ new ScoreObserver{SceneManager::GetInstance().GetEntityCounter(), {20.f,10.f}} };
	Observer* scoreObserver_01{ new ScoreObserver{SceneManager::GetInstance().GetEntityCounter(), {WINDOWWIDTH -200.f, 10.f}} };

	UNREFERENCED_PARAMETER(scoreObserver);
	UNREFERENCED_PARAMETER(scoreObserver_01);

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


}

void Game::InitializeLevel02()
{

	auto& scene = SceneManager::GetInstance().CreateScene("LEVEL_1");

	//RESET SUBJECT
	SceneManager::GetInstance().GetEntityCounter()->SetEnemiesAlive(4);

	std::shared_ptr<Level> pLevel = std::make_shared<Level>("tiles", 1, 32, scene);
	pLevel->LoadMap("./Data/RESIZE/level_01.map", 20, 15);



	std::shared_ptr<GameObject> dino = std::make_shared<GameObject>("dino", false);
	dino->AddComponent<Transform>(320, 240, 0, 0, 32, 32, 1);
	dino->AddComponent<PlayerSM>();
	dino->AddComponent<PlayerComponent>(1);
	auto& sprite = dino->AddComponent<SpriteComponent>("dino", "idle_right", 2, 200, false);
	dino->AddComponent<RigidBodyComponent>();
	dino->AddComponent<ColliderComponent>("PLAYER");
	dino->AddComponent<KeyboardInputComponent>("left", "right", "up", "space");
	sprite.AddAnimation("moving_right", 1, 2, 200);
	sprite.AddAnimation("shoot_right", 2, 1, 10);
	sprite.AddAnimation("jumping_right", 3, 1, 100);
	sprite.AddAnimation("idle_left", 4, 2, 200);
	sprite.AddAnimation("moving_left", 5, 2, 200);
	sprite.AddAnimation("shoot_left", 6, 1, 10);
	sprite.AddAnimation("jumping_left", 7, 1, 100);
	scene.Add(dino);

	std::shared_ptr<GameObject> clockworker = std::make_shared<GameObject>("clockworker", false);
	clockworker->AddComponent<Transform>(80, 200, 0, 0, 32, 32, 1);
	clockworker->AddComponent<SpriteComponent>("maita", "standard", 2, 200, false);
	clockworker->AddComponent<RigidBodyComponent>();
	clockworker->AddComponent<ColliderComponent>("ENEMY");
	clockworker->AddComponent<EnemySM>(dino, EnemyType::Throw);
	scene.Add(clockworker);

}

void Game::InitializeLevel03()
{
	auto& scene = SceneManager::GetInstance().CreateScene("LEVEL_2");
}