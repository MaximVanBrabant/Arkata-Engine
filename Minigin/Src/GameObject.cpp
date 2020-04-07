#include "MiniginPCH.h"
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "Transform.h"



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

void dae::GameObject::ListComponents() const
{
	std::cout << "gameObject " << m_Name << " has these components attached to it: \n";
	for (std::shared_ptr<Component> pComponent : m_pComponents)
	{
		const char* type = typeid(*pComponent).name();
		if (type == typeid(Transform).name())
		{
			std::cout << "transform component " << std::endl;
		}
		else if (type == typeid(SpriteComponent).name())
		{
			std::cout << "sprite component " << std::endl;
		}
	}
}

const std::shared_ptr<dae::Component>& dae::GameObject::GetTransform() const
{
	for (const std::shared_ptr<dae::Component>& component : m_pComponents)
	{
		auto type = typeid(*component).name();
		if (type == typeid(Transform).name())
		{
			return component;
		}
	}
	throw std::exception("No transform component found on this gameObject");
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

//const Transform& dae::GameObject::GetTransform() const
//{
//	for (Component* p : m_pComponents)
//	{
//		
//	}
//}
