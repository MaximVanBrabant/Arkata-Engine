#include "MiniginPCH.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerSM.h"
#include "PlayerComponent.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "KeyboardInputComponent.h"
#include "SpriteComponent.h"
#include "ScoreObserver.h"
#include "Constants.h"

#include <SDL.h>

bool dae::InputManager::ProcessInput()
{
	//controller
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_PollEvent(&m_Event);
	switch (m_Event.type)
	{
	case SDL_KEYDOWN:
		switch (m_Event.key.keysym.sym)
		{
		case SDLK_KP_ENTER:
			if(!m_SecondPlayerAdded)
				AddSecondPLayer();
			break;
		}

		break;
	case SDL_QUIT:
		return false;
		break;
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

void dae::InputManager::AddSecondPLayer()
{
	m_SecondDino = std::make_shared<GameObject>("dino_01", false);
	m_SecondDino->AddComponent<Transform>(300, 240, 0, 0, 32, 32, 1);
	m_SecondDino->AddComponent<PlayerSM>();
	m_SecondDino->AddComponent<PlayerComponent>(2);
	auto& sprite_01 = m_SecondDino->AddComponent<SpriteComponent>("dino_00", "idle_right", 2, 200, false);
	m_SecondDino->AddComponent<RigidBodyComponent>();
	m_SecondDino->AddComponent<ColliderComponent>("PLAYER");
	m_SecondDino->AddComponent<KeyboardInputComponent>("a", "d", "w", "s");
	sprite_01.AddAnimation("moving_right", 1, 2, 200);
	sprite_01.AddAnimation("shoot_right", 2, 1, 10);
	sprite_01.AddAnimation("jumping_right", 3, 1, 100);
	sprite_01.AddAnimation("idle_left", 4, 2, 200);
	sprite_01.AddAnimation("moving_left", 5, 2, 200);
	sprite_01.AddAnimation("shoot_left", 6, 1, 10);
	sprite_01.AddAnimation("jumping_left", 7, 1, 100);
	SceneManager::GetInstance().AddGameObjectToAllScenes(m_SecondDino);


	Observer* scoreObserver_01{ new ScoreObserver{SceneManager::GetInstance().GetEntityCounter(), {WINDOWWIDTH - 200.f, 10.f}} };
	UNREFERENCED_PARAMETER(scoreObserver_01);
	m_SecondPlayerAdded = true;
}

