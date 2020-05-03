#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "Collision.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

int dae::Scene::GetId() const
{
	return m_Id;
}

void dae::Scene::ListAllEntities() const
{
	for (auto& object : m_Objects)
	{
		std::cout << "name of the entity: " << object->GetName() << " here are the components: \n";
		object->ListComponents();
	}
}

//first scene has index 0
Scene::Scene(const std::string& name) : m_Name(name), m_Id{ m_IdCounter } { ++m_IdCounter; }

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{

	//TODO: check first if the object is active or not
	for (int i{}; i < m_Objects.size(); ++i)
	{
		auto& object = m_Objects[i];

		if (object->IsActive())
		{
			object->Update(deltaTime);
		}
		else
		{
			m_NonActiveIndices.push_back(i);
		}
	}

	//delete inactive objects
	for (int index : m_NonActiveIndices)
	{
		m_Objects[index] = m_Objects[m_Objects.size() - 1];
		m_Objects.pop_back();
	}

	CheckGameObjectCollisions();
	m_NonActiveIndices.clear();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void dae::Scene::ApplyCollisionEffects(CollisionInfo collisionInfo)
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
		//tile collision
		std::cout << "tile collision" << std::endl;
	}
}

CollisionInfo dae::Scene::CheckGameObjectCollisions()
{
	for (int i{ 0 }; i < m_Objects.size() - 1; ++i)
	{
		auto& firstGameObject = m_Objects[i];
		if (firstGameObject->HasComponent<ColliderComponent>())
		{
			ColliderComponent* firstCollider = firstGameObject->GetComponent<ColliderComponent>();
			for (int j{ i + 1 }; j < m_Objects.size(); ++j)
			{
				auto& secondGameObject = m_Objects[j];
				if (firstGameObject->GetName().compare(secondGameObject->GetName()) != 0 && secondGameObject->HasComponent<ColliderComponent>())
				{
					ColliderComponent* secondCollider = secondGameObject->GetComponent<ColliderComponent>();
					if (Collision::CheckRectangleCollision(firstCollider->GetCollider(), secondCollider->GetCollider()))
					{
						const std::string& firstTag = firstCollider->GetTag();
						const std::string& secondTag = secondCollider->GetTag();

						if(Collision::CheckCollisionTypeWithTags(firstTag, secondTag, "ENEMY", "PLAYER"))
						{
							if(firstTag.compare("PLAYER") == 0)
								ApplyCollisionEffects( CollisionInfo(CollisionType::PLAYER_ENEMY_COLLISION, firstGameObject, secondGameObject));
							else
								ApplyCollisionEffects (CollisionInfo(CollisionType::PLAYER_ENEMY_COLLISION, secondGameObject, firstGameObject));
							continue;

						}
						if (Collision::CheckCollisionTypeWithTags(firstTag, secondTag, "TILE", "PLAYER"))
						{
							//this check is necessary to know which one is the first gameobject 
							if (firstTag.compare("PLAYER") == 0)
								ApplyCollisionEffects (CollisionInfo{ CollisionType::PLAYER_TILE_COLLISION, firstGameObject, secondGameObject });
							else
								ApplyCollisionEffects( CollisionInfo{ CollisionType::PLAYER_TILE_COLLISION, secondGameObject, firstGameObject });
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
		}
	}
	return CollisionInfo(CollisionType::NO_COLLISION, nullptr, nullptr);
}

