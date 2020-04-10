#include "MiniginPCH.h"
#include "KeyboardInputComponent.h"
#include "Transform.h"
#include "SpriteComponent.h"
#include <SDL.h>
#include "InputManager.h"
#include "GameObject.h"

dae::KeyboardInputComponent::KeyboardInputComponent(const std::string& leftKey, const std::string& rightKey, const std::string& shootKey, const std::string& jumpKey)
{
	m_LeftInput = GetSDLKeyStringCode(leftKey);
	m_RightInput = GetSDLKeyStringCode(rightKey);
	m_ShootInput = GetSDLKeyStringCode(shootKey);
	m_JumpInput = GetSDLKeyStringCode(jumpKey);

}

std::string dae::KeyboardInputComponent::GetSDLKeyStringCode(const std::string& input)
{
	//TODO: all the different keys
	if (input.compare("left") == 0) return std::to_string(SDLK_LEFT);
	if (input.compare("right") == 0) return std::to_string(SDLK_RIGHT);
	if (input.compare("up") == 0) return std::to_string(SDLK_UP);
	if (input.compare("space") == 0) return std::to_string(SDLK_SPACE);
	return std::to_string(static_cast<int>(input[0]));
}

void dae::KeyboardInputComponent::Initialize()
{
	m_pTransform = m_Owner->GetComponent<Transform>();
	m_pSprite = m_Owner->GetComponent<SpriteComponent>();
}

void dae::KeyboardInputComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	float velocity = 100;
	if (InputManager::GetInstance().m_Event.type == SDL_KEYDOWN)
	{
		std::string keyCode = std::to_string(InputManager::GetInstance().m_Event.key.keysym.sym);

		if (keyCode.compare(m_LeftInput) == 0)
		{
			m_pTransform->SetVelocity(-velocity, m_pTransform->GetVelocity().y);
			m_pSprite->Play("moving");
		}
		if (keyCode.compare(m_RightInput) == 0)
		{
			m_pTransform->SetVelocity(velocity, m_pTransform->GetVelocity().y);
			m_pSprite->Play("moving");
		}
		if (keyCode.compare(m_ShootInput) == 0)

		{
			std::cout << "space got pressed\n";
			m_pSprite->Play("shoot");
		}
		if (keyCode.compare(m_JumpInput) == 0)
		{

			m_pSprite->Play("jump");

		}
	}
	if (InputManager::GetInstance().m_Event.type == SDL_KEYUP)
	{
		std::string keyCode = std::to_string(InputManager::GetInstance().m_Event.key.keysym.sym);

		if (keyCode.compare(m_LeftInput) == 0)
		{
			m_pTransform->SetVelocity(0, 0);
			m_pSprite->Play("idle");
		}
		if (keyCode.compare(m_RightInput) == 0)
		{
			m_pTransform->SetVelocity(0, 0);
			m_pSprite->Play("idle");

		}
		if (keyCode.compare(m_ShootInput) == 0)
		{
			m_pSprite->Play("idle");
		}

	}
}