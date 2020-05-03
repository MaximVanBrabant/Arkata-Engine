#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

bool dae::InputManager::ProcessInput()
{
	//controller
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_PollEvent(&m_Event);
	switch (m_Event.type)
	{
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

