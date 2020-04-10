#include "MiniginPCH.h"
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"



dae::GameObject::GameObject()
	:m_IsActive{true}, m_Name{}, m_pComponents{}
{
}

dae::GameObject::GameObject(const std::string& name)
	:m_Name{name}, m_IsActive{true}, m_pComponents{}
{
}

dae::GameObject::~GameObject()
{
	m_ComponentTypeMap.clear();
	m_pComponents.clear();
}

void dae::GameObject::ListComponents() const
{
	for (auto& pair : m_ComponentTypeMap)
	{
		std::cout << pair.first->name() << std::endl;
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (const std::shared_ptr<Component>& component : m_pComponents)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (const std::shared_ptr<Component>& component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::Destroy()
{
	//destroy it at the end of the game loop
	m_IsActive = false;
}
