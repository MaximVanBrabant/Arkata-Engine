#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

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
	for(const auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

