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
		const Transform& GetTransformComponent() const;

		//TextComponent
		const std::shared_ptr<TextComponent>& GetTextComponent() const;
		void AddTextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		void AddTextComponent(const std::shared_ptr<TextComponent>& pTextComponent);

		//RenderComponent
		const std::shared_ptr<RenderComponent>& GetRenderComponent() const;
		void AddRenderComponent(const std::shared_ptr<RenderComponent>& pRenderComponent);


		GameObject();
		~GameObject();
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
