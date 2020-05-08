#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "Collision.h"
#include "ColliderComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"

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
		collisionInfo.firstGameObject->Destroy();
	}
	else if (collisionInfo.collisionType == CollisionType::PLAYER_TILE_COLLISION || collisionInfo.collisionType == CollisionType::ENEMY_TILE_COLLISION)
	{
		//get colliders
		ColliderComponent* playerCollider{ collisionInfo.firstGameObject->GetComponent<ColliderComponent>() };
		ColliderComponent* tileCollider{ collisionInfo.secondGameObject->GetComponent<ColliderComponent>() };
		Transform* playerTransform{ collisionInfo.firstGameObject->GetComponent<Transform>() };
		RigidBodyComponent* playerRigid{collisionInfo.firstGameObject->GetComponent<RigidBodyComponent>()};

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
	else if (collisionInfo.collisionType == CollisionType::PLAYER_NONE_COLLISION)
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
}

void dae::CollisionManager::CheckGameObjectCollisions()
{
	auto& gameObjects = SceneManager::GetInstance().GetActiveScene()->GetGameObjects();

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->HasComponent<ColliderComponent>())
		{
			gameObject->GetComponent<ColliderComponent>()->SetIsColliding(false);
		}
	}

	for (int i{ 0 }; i < gameObjects.size() - 1; ++i)
	{
		auto& firstGameObject = gameObjects[i];
		if (firstGameObject->HasComponent<ColliderComponent>())
		{
			ColliderComponent* firstCollider = firstGameObject->GetComponent<ColliderComponent>();

			for (int j{ i + 1 }; j < gameObjects.size(); ++j)
			{
				auto& secondGameObject = gameObjects[j];
				if (firstGameObject->GetName().compare(secondGameObject->GetName()) != 0 && secondGameObject->HasComponent<ColliderComponent>())
				{
					ColliderComponent* secondCollider = secondGameObject->GetComponent<ColliderComponent>();
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
						if (Collision::CheckCollisionTypeWithTags(firstTag, secondTag, "TILE", "PLAYER"))
						{
							//this check is necessary to know which one is the first gameobject 
							if (firstTag.compare("PLAYER") == 0)
								ApplyCollisionEffects(CollisionInfo{ CollisionType::PLAYER_TILE_COLLISION, firstGameObject, secondGameObject });
							else
								ApplyCollisionEffects(CollisionInfo{ CollisionType::PLAYER_TILE_COLLISION, secondGameObject, firstGameObject });
							continue;
						}
						if (Collision::CheckCollisionTypeWithTags(firstTag, secondTag, "ENEMY", "TILE"))
						{
							if (firstTag.compare("ENEMY") == 0)
								ApplyCollisionEffects(CollisionInfo{ CollisionType::ENEMY_TILE_COLLISION, firstGameObject, secondGameObject });
							else
								ApplyCollisionEffects(CollisionInfo{ CollisionType::ENEMY_TILE_COLLISION, secondGameObject, firstGameObject });
							continue;
						}
					}
				}

			}
				if (!firstCollider->GetIsColliding())
				{
					if (firstGameObject->GetComponent<ColliderComponent>()->GetTag().compare("PLAYER") == 0)
					{
						//he didnt collide with anything so he is not grounded
						ApplyCollisionEffects(CollisionInfo{ CollisionType::PLAYER_NONE_COLLISION, firstGameObject, nullptr });
					}
				}
		}
	}
	ApplyCollisionEffects(CollisionInfo(CollisionType::NO_COLLISION, nullptr, nullptr));
}