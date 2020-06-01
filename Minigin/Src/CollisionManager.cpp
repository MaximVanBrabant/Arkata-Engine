#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "Collision.h"
#include "ColliderComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "EnemySM.h"
#include "JumpEnemyState.h"
#include <thread>


void dae::CollisionManager::CollisionUpdate()
{
	CheckGameObjectCollisions();
}

void dae::CollisionManager::ApplyCollisionEffects(CollisionInfo collisionInfo)
{
	
	if (collisionInfo.collisionType == CollisionType::NO_COLLISION)
	{
		return;
	}
	else if (collisionInfo.collisionType == CollisionType::PLAYER_ENEMY_COLLISION)
	{
		//collisionInfo.firstGameObject->Destroy();
	}
	//else if (collisionInfo.collisionType == CollisionType::PLAYER_TILE_COLLISION || collisionInfo.collisionType == CollisionType::ENEMY_TILE_COLLISION || collisionInfo.collisionType == CollisionType::ITEM_TILE_COLLISION)
	else if(collisionInfo.collisionType == CollisionType::RIGID_TILE_COLLISION) //->>> debatable if this is the right thing
	{
		//get colliders
		//first check if i have those components on the gameobjects
		ColliderComponent* playerCollider{ collisionInfo.firstGameObject->GetComponent<ColliderComponent>() };
		ColliderComponent* tileCollider{ collisionInfo.secondGameObject->GetComponent<ColliderComponent>() };
		Transform* playerTransform{ collisionInfo.firstGameObject->GetComponent<Transform>() };
		RigidBodyComponent* playerRigid{collisionInfo.firstGameObject->GetComponent<RigidBodyComponent>()};

		if (abs(playerCollider->GetCenterX() - tileCollider->GetCenterX()) == abs(playerCollider->GetCenterY() - tileCollider->GetCenterY()))
		{
			return;
		}

		if (abs(playerCollider->GetCenterX() - tileCollider->GetCenterX()) < abs(playerCollider->GetCenterY() - tileCollider->GetCenterY()))
		{
			if (playerCollider->GetCenterY() < tileCollider->GetCenterY() && !playerCollider->GetIsGrounded() && playerTransform->GetVelocity().y > 0.0f)
			{
				playerTransform->SetPosition(playerTransform->GetPosition().x, static_cast<float>(tileCollider->GetCollider().y - tileCollider->GetCollider().h));
				playerTransform->SetVelocity(playerTransform->GetVelocity().x, 0);
				playerRigid->EnableGravity(false);
				playerCollider->SetIsGrounded(true);
			}
		}
		else
		{
			//the GetisGrounded makes sure i cant walk through walls
			if (playerTransform->GetVelocity().y > 0.0f || playerCollider->GetIsGrounded())
			{
				if (playerCollider->GetCenterX() < tileCollider->GetCenterX())
				{
					playerTransform->SetPosition(static_cast<float>(tileCollider->GetCollider().x - playerCollider->GetCollider().w), playerTransform->GetPosition().y);
				}
				if (playerCollider->GetCenterX() > tileCollider->GetCenterX())
				{
					playerTransform->SetPosition(static_cast<float>(tileCollider->GetCollider().x + tileCollider->GetCollider().w), playerTransform->GetPosition().y);

				}
			}

		}
	}
	else if (collisionInfo.collisionType == CollisionType::RIGID_HORIZONTAL_SOLID_TILE_COLLISION)
	{
		//get colliders
		//first check if i have those components on the gameobjects
		ColliderComponent* playerCollider{ collisionInfo.firstGameObject->GetComponent<ColliderComponent>() };
		ColliderComponent* tileCollider{ collisionInfo.secondGameObject->GetComponent<ColliderComponent>() };
		Transform* playerTransform{ collisionInfo.firstGameObject->GetComponent<Transform>() };
		RigidBodyComponent* playerRigid{ collisionInfo.firstGameObject->GetComponent<RigidBodyComponent>() };


		//getisgrouneded and > 0.0f makes sure this doesnt check when youre still on the ground + when you jump otherwise it would instantly stick it to the ground again
		if (playerCollider->GetCenterY() < tileCollider->GetCenterY() && !playerCollider->GetIsGrounded() && playerTransform->GetVelocity().y > 0.0f)
		{
			playerTransform->SetPosition(playerTransform->GetPosition().x, static_cast<float>(tileCollider->GetCollider().y - tileCollider->GetCollider().h));
			playerTransform->SetVelocity(playerTransform->GetVelocity().x, 0);
			playerRigid->EnableGravity(false);
			playerCollider->SetIsGrounded(true);
		}
		if (playerCollider->GetCenterY() > tileCollider->GetCenterY() && !playerCollider->GetIsGrounded() && playerTransform->GetVelocity().y < 0.0f)
		{
			playerTransform->SetPosition(playerTransform->GetPosition().x, static_cast<float>(tileCollider->GetCollider().y + tileCollider->GetCollider().h));
			playerTransform->SetVelocity(playerTransform->GetVelocity().x, 0);

		}

	}
	else if (collisionInfo.collisionType == CollisionType::RIGID_VERTICAL_SOLID_TILE_COLLISION)
	{
		//get colliders
		//first check if i have those components on the gameobjects
		ColliderComponent* playerCollider{ collisionInfo.firstGameObject->GetComponent<ColliderComponent>() };
		ColliderComponent* tileCollider{ collisionInfo.secondGameObject->GetComponent<ColliderComponent>() };
		Transform* playerTransform{ collisionInfo.firstGameObject->GetComponent<Transform>() };

		//the GetisGrounded makes sure i cant walk through walls

		if (playerCollider->GetCenterX() < tileCollider->GetCenterX())
		{
			playerTransform->SetPosition(static_cast<float>(tileCollider->GetCollider().x - playerCollider->GetCollider().w), playerTransform->GetPosition().y);
		}
		if (playerCollider->GetCenterX() > tileCollider->GetCenterX())
		{
			playerTransform->SetPosition(static_cast<float>(tileCollider->GetCollider().x + tileCollider->GetCollider().w), playerTransform->GetPosition().y);

		}


	}
	else if (collisionInfo.collisionType == CollisionType::ENEMY_ENEMY_COLLISION)
	{
		ColliderComponent* playerCollider{ collisionInfo.firstGameObject->GetComponent<ColliderComponent>() };
		ColliderComponent* tileCollider{ collisionInfo.secondGameObject->GetComponent<ColliderComponent>() };
		Transform* playerTransform{ collisionInfo.firstGameObject->GetComponent<Transform>() };
		if (abs(playerCollider->GetCenterX() - tileCollider->GetCenterX()) == abs(playerCollider->GetCenterY() - tileCollider->GetCenterY()))
		{
			return;
		}

		if (abs(playerCollider->GetCenterX() - tileCollider->GetCenterX()) < abs(playerCollider->GetCenterY() - tileCollider->GetCenterY()))
		{
			if (playerCollider->GetCenterY() < tileCollider->GetCenterY() && !playerCollider->GetIsGrounded() && playerTransform->GetVelocity().y > 0.0f)
			{
				playerTransform->SetPosition(playerTransform->GetPosition().x, static_cast<float>(tileCollider->GetCollider().y - tileCollider->GetCollider().h));
				playerTransform->SetVelocity(playerTransform->GetVelocity().x, 0);
				//playerRigid->EnableGravity(false);
				//playerCollider->SetIsGrounded(true);
			}
		}
		else
		{
			if (playerCollider->GetCenterX() < tileCollider->GetCenterX())
			{
				playerTransform->SetPosition(static_cast<float>(tileCollider->GetCollider().x - playerCollider->GetCollider().w), playerTransform->GetPosition().y);
			}
			if (playerCollider->GetCenterX() > tileCollider->GetCenterX())
			{
				playerTransform->SetPosition(static_cast<float>(tileCollider->GetCollider().x + tileCollider->GetCollider().w), playerTransform->GetPosition().y);

			}
		}

		//move them away from eachother
		if (collisionInfo.firstGameObject->HasComponent<EnemySM>())
		{
			auto enemySM = collisionInfo.firstGameObject->GetComponent<EnemySM>();
			enemySM->SetInverseMovement(true);
		}


	}
	else if (collisionInfo.collisionType == CollisionType::RIGID_NONE_COLLISION)
	{
		//you are in the air
		if (collisionInfo.firstGameObject->HasComponent<RigidBodyComponent>() && collisionInfo.firstGameObject->HasComponent<ColliderComponent>() && collisionInfo.firstGameObject->HasComponent<Transform>())
		{
			ColliderComponent* playerCollider{ collisionInfo.firstGameObject->GetComponent<ColliderComponent>() };
			RigidBodyComponent* playerRigid{ collisionInfo.firstGameObject->GetComponent<RigidBodyComponent>() };
			Transform* playerTransform{ collisionInfo.firstGameObject->GetComponent<Transform>() };

			if (playerCollider->GetIsGrounded())
			{
				playerCollider->SetIsGrounded(false);
				//instantly sets my velocity instead of gradually decreasing over time with the rigidbody gravity
				if (playerTransform->GetVelocity().y == 0)
					playerTransform->SetVelocity(playerTransform->GetVelocity().x, 200.f);
				playerRigid->EnableGravity(true);
			}
		}
	}
	else if (collisionInfo.collisionType == CollisionType::AI_FLOOR_TILE_COLLISION)
	{
		//std::cout << "ai collider collides with tile" << std::endl;
	}
	else if (collisionInfo.collisionType == CollisionType::AI_FLOOR_NONE_COLLISION)
	{
		if (collisionInfo.firstGameObject->HasComponent<EnemySM>())
		{
			auto enemySM = collisionInfo.firstGameObject->GetComponent<EnemySM>();
			auto enemyCollider = collisionInfo.firstGameObject->GetComponent<ColliderComponent>();
			if (enemyCollider->GetIsGrounded())
			{
				//here choose which jumpheight to use
			
				enemySM->SetJumpHeight(enemySM->GetHorizontalJumpHeight());
				enemySM->JumpIntoAir();
			}
		}
	}
	else if (collisionInfo.collisionType == CollisionType::AI_PLATFORM_TILE_COLLISION)
	{
		if (collisionInfo.firstGameObject->HasComponent<EnemySM>())
		{
			auto enemySM = collisionInfo.firstGameObject->GetComponent<EnemySM>();
			auto enemyCollider = collisionInfo.firstGameObject->GetComponent<ColliderComponent>();
			if (enemyCollider->GetIsGrounded())
			{
				//here choose which jumpheight to use
				enemySM->SetJumpHeight(enemySM->GetVerticalJumpHeight());
				enemySM->JumpIntoAir();
			}
		}
	}
	else if (collisionInfo.collisionType == CollisionType::AI_FLOOR_VERTICAL_SOLID_TILE_COLLISION)
	{
		if (collisionInfo.firstGameObject->HasComponent<EnemySM>())
		{
			auto enemySM = collisionInfo.firstGameObject->GetComponent<EnemySM>();
			auto enemyCollider = collisionInfo.firstGameObject->GetComponent<ColliderComponent>();
			if (enemyCollider->GetIsGrounded())
			{
				enemySM->SetInverseMovement(true);
			}
		}
	}
}

void dae::CollisionManager::CheckCollisionOnAIColliders(const std::vector<int>& vIndicesOfEnemies)
{
	//make a vector store all the enabled collider from the ai in it then iterate over them and give them specific tags so you know what to do
	//enable disable depending on the displacement vector
	//no need for the getter of the displacement vector

	auto& gameObjects = SceneManager::GetInstance().GetActiveScene()->GetGameObjects();

	for (int index : vIndicesOfEnemies)
	{
		auto& enemy = gameObjects[index];

		if (enemy->HasComponent<EnemySM>())
		{
			std::vector<ColliderComponent*> vAIColliders{};

			auto enemySM = enemy->GetComponent<EnemySM>();
			auto leftFloorCollider = enemySM->GetLeftFloorCollider();
			auto rightFloorCollider = enemySM->GetRightFloorCollider();
			auto leftPlatformCollider = enemySM->GetLeftPlatformCollider();
			auto rightPlatformCollider = enemySM->GetRightPlatformCollider();


			if (leftFloorCollider->GetEnabled())
			{
				vAIColliders.push_back(leftFloorCollider);
			}
			if (rightFloorCollider->GetEnabled())
			{
				vAIColliders.push_back(rightFloorCollider);
			}
			if (leftPlatformCollider->GetEnabled())
			{
				vAIColliders.push_back(leftPlatformCollider);
			}
			if (rightPlatformCollider->GetEnabled())
				vAIColliders.push_back(rightPlatformCollider);

			for (auto AICollider : vAIColliders)
			{
				AICollider->SetIsColliding(false);
				const std::string& AITag = AICollider->GetTag();

				for (int i{ 0 }; i < gameObjects.size(); ++i)
				{
					auto& otherGameObject = gameObjects[i];
					if (otherGameObject->HasComponent<ColliderComponent>() && otherGameObject->GetName().compare("tile") == 0)
					{
						ColliderComponent* otherCollider = otherGameObject->GetComponent<ColliderComponent>();
						const std::string& secondTag = otherCollider->GetTag();

						if (Collision::CheckRectangleCollision(AICollider->GetCollider(), otherCollider->GetCollider()))
						{
							AICollider->SetIsColliding(true);
							if (Collision::CheckCollisionTypeWithTags(AITag, secondTag, "AI_FLOOR", "TILE"))
							{
								if (AITag.compare("AI_FLOOR") == 0)
									ApplyCollisionEffects(CollisionInfo{ CollisionType::AI_FLOOR_TILE_COLLISION, enemy, otherGameObject });
								else
									ApplyCollisionEffects(CollisionInfo{ CollisionType::AI_FLOOR_TILE_COLLISION, otherGameObject, enemy });
								continue;
							}
							else if (Collision::CheckCollisionTypeWithTags(AITag, secondTag, "AI_PLATFORM", "TILE"))
							{
								if (AITag.compare("AI_PLATFORM") == 0)
									ApplyCollisionEffects(CollisionInfo{ CollisionType::AI_PLATFORM_TILE_COLLISION, enemy, otherGameObject });
								else
									ApplyCollisionEffects(CollisionInfo{ CollisionType::AI_PLATFORM_TILE_COLLISION, otherGameObject, enemy });
								continue;
							}
							else if (Collision::CheckCollisionTypeWithTags(AITag, secondTag, "AI_FLOOR", "VERTICAL_SOLID_TILE"))
							{
								if (AITag.compare("AI_FLOOR") == 0)
									ApplyCollisionEffects(CollisionInfo{ CollisionType::AI_FLOOR_VERTICAL_SOLID_TILE_COLLISION, enemy, otherGameObject });
								else
									ApplyCollisionEffects(CollisionInfo{ CollisionType::AI_FLOOR_VERTICAL_SOLID_TILE_COLLISION, otherGameObject, enemy });
								continue;
							}
						}

					}
				}

				if (!AICollider->GetIsColliding())
				{
					if(AITag.compare("AI_FLOOR") == 0)
						ApplyCollisionEffects(CollisionInfo{ CollisionType::AI_FLOOR_NONE_COLLISION, enemy, nullptr });
				}
			}

		}
	}

}

void dae::CollisionManager::CheckGameObjectCollisions()
{
	auto& gameObjects = SceneManager::GetInstance().GetActiveScene()->GetGameObjects();
	std::vector<int> vEnemyIndices{};

	for (int i{ 0 }; i < gameObjects.size(); ++i)
	{
		if (gameObjects[i]->HasComponent<ColliderComponent>())
		{
			gameObjects[i]->GetComponent<ColliderComponent>()->SetIsColliding(false);
		}
		if (gameObjects[i]->HasComponent<EnemySM>())
		{
			vEnemyIndices.push_back(i);
		}
	}

	//HERE YOU CAN USE THREAD
	CheckCollisionOnAIColliders(vEnemyIndices);

	

	for (int i{ 0 }; i < gameObjects.size(); ++i)
	{
		auto& firstGameObject = gameObjects[i];
		if (firstGameObject->HasComponent<ColliderComponent>())
		{
			ColliderComponent* firstCollider = firstGameObject->GetComponent<ColliderComponent>();

			if (!firstCollider->GetEnabled())
				continue;

			for (int j{ i + 1 }; j < gameObjects.size(); ++j)
			{
				auto& secondGameObject = gameObjects[j];
				if (firstGameObject->GetName().compare(secondGameObject->GetName()) != 0 && secondGameObject->HasComponent<ColliderComponent>())
				{
					ColliderComponent* secondCollider = secondGameObject->GetComponent<ColliderComponent>();

					if (!secondCollider->GetEnabled())
						continue;

					const std::string& firstTag = firstCollider->GetTag();
					const std::string& secondTag = secondCollider->GetTag();

					if (Collision::CheckRectangleCollision(firstCollider->GetCollider(), secondCollider->GetCollider()))
					{
						firstCollider->SetIsColliding(true);
						secondCollider->SetIsColliding(true);

						if (Collision::CheckCollisionTypeWithTags(firstTag, secondTag, "ENEMY", "PLAYER"))
						{
							if (firstTag.compare("PLAYER") == 0)
								ApplyCollisionEffects(CollisionInfo(CollisionType::PLAYER_ENEMY_COLLISION, firstGameObject, secondGameObject));
							else
								ApplyCollisionEffects(CollisionInfo(CollisionType::PLAYER_ENEMY_COLLISION, secondGameObject, firstGameObject));
							continue;

						}
						if (Collision::CheckCollisionTypeWithTags(firstTag, secondTag, "ENEMY", "ENEMY"))
						{
							ApplyCollisionEffects(CollisionInfo(CollisionType::ENEMY_ENEMY_COLLISION, firstGameObject, secondGameObject));
						}
						if (firstTag.compare("TILE") == 0 || secondTag.compare("TILE") == 0)
						{
							if (firstTag.compare("TILE") == 0)
							{
								if (secondGameObject->HasComponent<RigidBodyComponent>())
								{
									ApplyCollisionEffects(CollisionInfo{ CollisionType::RIGID_TILE_COLLISION, secondGameObject, firstGameObject });
									continue;
								}
							}
							else
							{
								if (firstGameObject->HasComponent<RigidBodyComponent>())
								{
									ApplyCollisionEffects(CollisionInfo{ CollisionType::RIGID_TILE_COLLISION, firstGameObject, secondGameObject });
									continue;
								}
							}
						}
						if (firstTag.compare("HORIZONTAL_SOLID_TILE") == 0 || secondTag.compare("HORIZONTAL_SOLID_TILE") == 0)
						{
							if (firstTag.compare("HORIZONTAL_SOLID_TILE") == 0)
							{
								if (secondGameObject->HasComponent<RigidBodyComponent>())
								{
									ApplyCollisionEffects(CollisionInfo{ CollisionType::RIGID_HORIZONTAL_SOLID_TILE_COLLISION, secondGameObject, firstGameObject });
									continue;
								}
							}
							else
							{
								if (firstGameObject->HasComponent<RigidBodyComponent>())
								{
									ApplyCollisionEffects(CollisionInfo{ CollisionType::RIGID_HORIZONTAL_SOLID_TILE_COLLISION, firstGameObject, secondGameObject });
									continue;
								}
							}
						}
						if (firstTag.compare("VERTICAL_SOLID_TILE") == 0 || secondTag.compare("VERTICAL_SOLID_TILE") == 0)
						{
							if (firstTag.compare("VERTICAL_SOLID_TILE") == 0)
							{
								if (secondGameObject->HasComponent<RigidBodyComponent>())
								{
									ApplyCollisionEffects(CollisionInfo{ CollisionType::RIGID_VERTICAL_SOLID_TILE_COLLISION, secondGameObject, firstGameObject });
									continue;
								}
							}
							else
							{
								if (firstGameObject->HasComponent<RigidBodyComponent>())
								{
									ApplyCollisionEffects(CollisionInfo{ CollisionType::RIGID_VERTICAL_SOLID_TILE_COLLISION, firstGameObject, secondGameObject });
									continue;
								}
							}
						}
					}
				}

			}

			if (!firstCollider->GetIsColliding())
			{
				if (firstGameObject->HasComponent<RigidBodyComponent>())
				{
					//he didnt collide with anything so he is not grounded
					ApplyCollisionEffects(CollisionInfo{ CollisionType::RIGID_NONE_COLLISION, firstGameObject, nullptr });
				}
			}
		}
	}
}