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
Scene::Scene(const std::string& name) : m_Name(name), m_Id{ m_IdCounter } { ++m_IdCounter; }

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{

	//MAKE USE OF THREADS HERE !!!!!

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

