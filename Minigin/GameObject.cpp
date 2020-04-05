#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"


using namespace dae;

GameObject::GameObject()
	:m_Transform{}, m_pRenderComponent{ nullptr }, m_pTextComponent{nullptr}
{

}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_pTextComponent)
	{
		m_pTextComponent->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	if (m_pRenderComponent)
	{
		m_pRenderComponent->Render(m_Transform);
	}
	if (m_pTextComponent)
	{
		m_pTextComponent->Render();
	}
}


const Transform& dae::GameObject::GetTransformComponent() const
{
	return m_Transform;
}

const std::shared_ptr<RenderComponent>& dae::GameObject::GetRenderComponent() const
{
	return m_pRenderComponent;
}

const std::shared_ptr<TextComponent>& dae::GameObject::GetTextComponent() const
{

	return m_pTextComponent;
}

void dae::GameObject::AddTextComponent(const std::string& text, const std::shared_ptr<Font>& font)
{
	m_pTextComponent = std::make_shared<TextComponent>(text, font);
}

void dae::GameObject::AddTextComponent(const std::shared_ptr<TextComponent>& pTextComponent)
{
	if (m_pTextComponent == nullptr)
	{
		m_pTextComponent = pTextComponent;
	}
	else
	{
		std::cerr << "gameObject already has a textComponent\n";
	}
}

void dae::GameObject::AddRenderComponent(const std::shared_ptr<RenderComponent>& pRenderComponent)
{
	m_pRenderComponent = pRenderComponent;
}
