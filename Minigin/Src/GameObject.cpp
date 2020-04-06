#include "MiniginPCH.h"
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"



dae::GameObject::GameObject()
	:m_IsActive{true}, m_Name{}, m_pComponents{}
{
}

dae::GameObject::GameObject(const std::string& name)
	:m_Name{name}, m_IsActive{true}, m_pComponents{}
{
}

dae::GameObject::GameObject(const GameObject & other)
{
	m_IsActive = other.m_IsActive;
	m_Name = other.m_Name;
	m_pComponents = other.m_pComponents;
}

void dae::GameObject::Update(float deltaTime)
{
	for (std::shared_ptr<Component> component : m_pComponents)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (std::shared_ptr<Component> component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::Destroy()
{
	//destroy it at the end of the game loop
	m_IsActive = false;
}

//const Transform& dae::GameObject::GetTransform() const
//{
//	for (Component* p : m_pComponents)
//	{
//		
//	}
//}
