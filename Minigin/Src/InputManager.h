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

	class GameObject;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		bool IsSecondPlayerJoined() const { return m_SecondPlayerAdded; }
		SDL_Event m_Event;

		const std::shared_ptr<GameObject>& GetSecondDino() const { return m_SecondDino; }
	private:
		XINPUT_STATE m_CurrentState{};

		void AddSecondPLayer();

		bool m_SecondPlayerAdded = false;

		std::shared_ptr<GameObject> m_SecondDino = nullptr;
	};

}
