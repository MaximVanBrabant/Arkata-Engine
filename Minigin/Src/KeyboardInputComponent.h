#pragma once
#include "Component.h"

//only put this component on an object if you already have a sprite + transform component on the object
namespace dae
{
	class Transform;
	class SpriteComponent;
	class KeyboardInputComponent : public Component
	{
	public:
		KeyboardInputComponent() = default;
		KeyboardInputComponent(const std::string& leftKey, const std::string& rightKey, const std::string& shootKey, const std::string& jumpKey);
		void Initialize() override;
		void Update(float deltaTime) override;
	private:
		std::string m_LeftInput;
		std::string m_RightInput;
		std::string m_ShootInput;
		std::string m_JumpInput;
		Transform* m_pTransform;
		SpriteComponent* m_pSprite;

		//this makes sure our movement doens't glitch
		bool leftPress = false;
		bool rightPress = false;

		std::string GetSDLKeyStringCode(const std::string& input);
	};
}

