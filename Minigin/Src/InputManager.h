#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		SDL_Event m_Event;
	private:
		XINPUT_STATE m_CurrentState{};
	};

}
