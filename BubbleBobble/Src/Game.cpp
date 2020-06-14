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
#include "InputManager.h"
#include "VersusEnemySM.h"

using namespace dae;

Game::Game()
{
	InitializeLevel01();
	InitializeLevel02();
	InitializeLevel03();
	InitializeLevel04();
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
	SceneManager::GetInstance().GetEntityCounter()->SetEnemiesAlive(2);

	//ENEMIES KILLED OBSERVER
	KillObserver* killObserver{ new KillObserver{SceneManager::GetInstance().GetEntityCounter()} };
	UNREFERENCED_PARAMETER(killObserver);

	//LEVEL
	std::shared_ptr<Level> pLevel = std::make_shared<Level>("tiles", 1, 32, scene);
	pLevel->LoadMap("./Data/RESIZE/level.map", 20, 15);

	// 1 PLAYER
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

	//SCORE PLAYER 1
	Observer* scoreObserver{ new ScoreObserver{SceneManager::GetInstance().GetEntityCounter(), {20.f,10.f}} };
	UNREFERENCED_PARAMETER(scoreObserver);


	////ENEMIES

	std::shared_ptr<GameObject> clockworker = std::make_shared<GameObject>("clockworker", false);
	clockworker->AddComponent<Transform>(80, 50, 0, 0, 32, 32, 1);
	clockworker->AddComponent<SpriteComponent>("maita", "standard", 2,200, false);
	clockworker->AddComponent<RigidBodyComponent>();
	clockworker->AddComponent<ColliderComponent>("ENEMY");
	clockworker->AddComponent<EnemySM>(dino, EnemyType::Throw);
	scene.Add(clockworker);

	std::shared_ptr<GameObject> clockworker_1 = std::make_shared<GameObject>("clockworker_1", false);
	clockworker_1->AddComponent<Transform>(250, 50, 0, 0, 32, 32, 1);
	clockworker_1->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	clockworker_1->AddComponent<RigidBodyComponent>();
	clockworker_1->AddComponent<ColliderComponent>("ENEMY");
	clockworker_1->AddComponent<EnemySM>(dino, EnemyType::Charge);
	scene.Add(clockworker_1);




}

void Game::InitializeLevel02()
{

	auto& scene = SceneManager::GetInstance().CreateScene("LEVEL_1");

	//STANDARD GAME
	std::shared_ptr<Level> pLevel = std::make_shared<Level>("tiles", 1, 32, scene);
	pLevel->LoadMap("./Data/RESIZE/level_01.map", 20, 15);


	// 1 PLAYER
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


	//ENEMIES
	std::shared_ptr<GameObject> maita = std::make_shared<GameObject>("maita", false);
	maita->AddComponent<Transform>(80, 200, 0, 0, 32, 32, 1);
	maita->AddComponent<SpriteComponent>("maita", "standard", 2, 200, false);
	maita->AddComponent<RigidBodyComponent>();
	maita->AddComponent<ColliderComponent>("ENEMY");
	maita->AddComponent<EnemySM>(dino, EnemyType::Throw);
	scene.Add(maita);

	std::shared_ptr<GameObject> clockworker_3 = std::make_shared<GameObject>("clockworker_3", false);
	clockworker_3->AddComponent<Transform>(250, 350, 0, 0, 32, 32, 1);
	clockworker_3->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	clockworker_3->AddComponent<RigidBodyComponent>();
	clockworker_3->AddComponent<ColliderComponent>("ENEMY");
	clockworker_3->AddComponent<EnemySM>(dino, EnemyType::Charge);
	scene.Add(clockworker_3);


	std::shared_ptr<GameObject> maita_01 = std::make_shared<GameObject>("maita_01", false);
	maita_01->AddComponent<Transform>(300, 200, 0, 0, 32, 32, 1);
	maita_01->AddComponent<SpriteComponent>("maita", "standard", 2, 200, false);
	maita_01->AddComponent<RigidBodyComponent>();
	maita_01->AddComponent<ColliderComponent>("ENEMY");
	maita_01->AddComponent<EnemySM>(dino, EnemyType::Throw);
	scene.Add(maita_01);
}

void Game::InitializeLevel03()
{
	auto& scene = SceneManager::GetInstance().CreateScene("LEVEL_2");

	std::shared_ptr<Level> pLevel = std::make_shared<Level>("tiles", 1, 32, scene);
	pLevel->LoadMap("./Data/RESIZE/level_02.map", 20, 15);

	// 1 PLAYER
	std::shared_ptr<GameObject> dino = std::make_shared<GameObject>("dino", false);
	dino->AddComponent<Transform>(80, 240, 0, 0, 32, 32, 1);
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


	//ENEMIES
	std::shared_ptr<GameObject> maita = std::make_shared<GameObject>("maita", false);
	maita->AddComponent<Transform>(500, 200, 0, 0, 32, 32, 1);
	maita->AddComponent<SpriteComponent>("maita", "standard", 2, 200, false);
	maita->AddComponent<RigidBodyComponent>();
	maita->AddComponent<ColliderComponent>("ENEMY");
	maita->AddComponent<EnemySM>(dino, EnemyType::Throw);
	scene.Add(maita);

	std::shared_ptr<GameObject> clockworker_2 = std::make_shared<GameObject>("clockworker_2", false);
	clockworker_2->AddComponent<Transform>(400, 100, 0, 0, 32, 32, 1);
	clockworker_2->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	clockworker_2->AddComponent<RigidBodyComponent>();
	clockworker_2->AddComponent<ColliderComponent>("ENEMY");
	clockworker_2->AddComponent<EnemySM>(dino, EnemyType::Charge);
	scene.Add(clockworker_2);


	std::shared_ptr<GameObject> clockworker_3 = std::make_shared<GameObject>("clockworker_3", false);
	clockworker_3->AddComponent<Transform>(250, 350, 0, 0, 32, 32, 1);
	clockworker_3->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	clockworker_3->AddComponent<RigidBodyComponent>();
	clockworker_3->AddComponent<ColliderComponent>("ENEMY");
	clockworker_3->AddComponent<EnemySM>(dino, EnemyType::Charge);
	scene.Add(clockworker_3);

	std::shared_ptr<GameObject> clockworker_4 = std::make_shared<GameObject>("clockworker_4", false);
	clockworker_4->AddComponent<Transform>(120, 80, 0, 0, 32, 32, 1);
	clockworker_4->AddComponent<SpriteComponent>("clockworker", "standard", 2, 200, false);
	clockworker_4->AddComponent<RigidBodyComponent>();
	clockworker_4->AddComponent<ColliderComponent>("ENEMY");
	clockworker_4->AddComponent<EnemySM>(dino, EnemyType::Charge);
	scene.Add(clockworker_4);

}

void dae::Game::InitializeLevel04()
{
	//VERSUS MODE

	auto& scene = SceneManager::GetInstance().CreateScene("LEVEL_3");

	std::shared_ptr<Level> pLevel = std::make_shared<Level>("tiles", 1, 32, scene);
	pLevel->LoadMap("./Data/RESIZE/level.map", 20, 15);


	// 1 PLAYER
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

	//VERSUS
	std::shared_ptr<GameObject> enemyPlayerMaita = std::make_shared<GameObject>("EnemyMaita", false);
	enemyPlayerMaita->AddComponent<Transform>(250, 50, 0, 0, 32, 32, 1);
	enemyPlayerMaita->AddComponent<SpriteComponent>("maita", "standard", 2, 200, false);
	enemyPlayerMaita->AddComponent<RigidBodyComponent>();
	enemyPlayerMaita->AddComponent<ColliderComponent>("MAITA_PLAYER");
	enemyPlayerMaita->AddComponent<KeyboardInputComponent>("f", "h", "g", "t");
	enemyPlayerMaita->AddComponent<VersusEnemySM>(dino);
	scene.Add(enemyPlayerMaita);
}

