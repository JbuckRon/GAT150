#include "InputSystem.h"
#include "Core/Logger.h"
#include <iostream>
#include <SDL.h>

namespace neu {
	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_shift = SDL_SCANCODE_LSHIFT;
	extern const uint32_t key_up = SDL_SCANCODE_UP;
	extern const uint32_t key_down = SDL_SCANCODE_DOWN;
	extern const uint32_t key_left = SDL_SCANCODE_LEFT;
	extern const uint32_t key_right = SDL_SCANCODE_RIGHT;
	extern const uint32_t key_escape = SDL_SCANCODE_ESCAPE;

	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;

	void InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numkeys);

		m_keyboardState.resize(m_numkeys);

		std::copy(keyboardState, keyboardState + m_numkeys, m_keyboardState.begin());

		m_prevKeyboardState = m_keyboardState;

	}

	void InputSystem::Shutdown()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		// save previous keyboard state
		m_prevKeyboardState = m_keyboardState;
		// get current keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());
	}

	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		// save previous keyboard state
		m_prevKeyboardState = m_keyboardState;

		//getcurrent keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_numkeys, m_keyboardState.begin());

		//std::cout << m_keyboardState[SDL_SCANCODE_SPACE] << std::endl;

		for (auto state : m_keyboardState)
		{
			//std::cout << (bool)state;
		}
		//std::cout << std::endl;

		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = neu::Vector2{ x , y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML]
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML]
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML]
	}
	InputSystem::KeyState InputSystem::GetKeyState(uint32_t key)
	{
		KeyState keyState = KeyState::Idle;

		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);
		// set the keyState if keyDown (true) and prevKeyDown (true)
		if (keyDown && prevKeyDown)
		{
			keyState = KeyState::Held;
		}
		// set the keyState if keyDown (true) and prevKeyDown (false)
		if (keyDown && !prevKeyDown)
		{
			keyState = KeyState::Released;
		}
		// set the keyState if keyDown (false) and prevKeyDown (true)
		if (!keyDown && prevKeyDown)
		{
			keyState = KeyState::Pressed;
		}
		// set the keyState if keyDown (false) and prevKeyDown (false)
		if (!keyDown && !prevKeyDown)
		{
			keyState = KeyState::Idle;
		}

		return keyState;

	}
	InputSystem::KeyState InputSystem::GetButtonState(uint32_t button)
	{
		KeyState keyState = KeyState::Idle;
		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);
		
		if (buttonDown && prevButtonDown)
		{
			keyState = KeyState::Held;
		}
		
		if (buttonDown && !prevButtonDown)
		{
			keyState = KeyState::Released;
		}
		
		if (!buttonDown && prevButtonDown)
		{
			keyState = KeyState::Pressed;
		}
		
		if (!buttonDown && !prevButtonDown)
		{
			keyState = KeyState::Idle;
		}
		
		return keyState;
	}
}