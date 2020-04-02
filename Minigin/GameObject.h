#pragma once
#include "RenderComponent.h"
#include "TextComponent.h"

namespace dae
{
	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render() const;

		//Transform
		Transform GetTransformComponent() const;

		//TextComponent
		std::shared_ptr<TextComponent> GetTextComponent() const;
		void AddTextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		void AddTextComponent(std::shared_ptr<TextComponent> pTextComponent);

		//RenderComponent
		std::shared_ptr<RenderComponent> GetRenderComponent() const;
		void AddRenderComponent(std::shared_ptr<RenderComponent> pRenderComponent);


		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::shared_ptr<RenderComponent> m_pRenderComponent;
		std::shared_ptr<TextComponent> m_pTextComponent;
	};
}
