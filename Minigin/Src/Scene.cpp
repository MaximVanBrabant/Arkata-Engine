#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "CollisionManager.h"

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
Scene::Scene(const std::string& name) : m_Name(name), m_Id{ m_IdCounter }
{
	++m_IdCounter;
}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{

	//MAKE USE OF THREADS HERE !!!!!

	for (int i{}; i < static_cast<int>(m_Objects.size()); ++i)
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

	//first chck if one of the inactive objects is the last one
	// this is really important because otherwise we would push the last element somewhere randomly in the vector and if that 
	// object needed to be deleted we won't be able because we still have the index of its previous position (the last position in the vector)
	bool lastItem = false;
	do
	{
		for (int index : m_NonActiveIndices)
		{
			if (index == static_cast<int>(m_Objects.size() - 1))
			{
				lastItem = true;
				m_Objects.pop_back();
				break;
			}
			else
			{
				lastItem = false;
			}
		}
	} while (lastItem);


	//delete inactive objects
	for (int index : m_NonActiveIndices)
	{
		if (index < static_cast<int>(m_Objects.size() - 1))
		{
			m_Objects[index] = m_Objects[m_Objects.size() - 1];
			m_Objects.pop_back();
		}
	}

	CollisionManager::GetInstance().CollisionUpdate();
	m_NonActiveIndices.clear();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

