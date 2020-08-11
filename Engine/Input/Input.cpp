#include "pch.h"
#include "Input.h"

namespace AZ {
	bool inputSystem::startup(){
		const Uint8* keystate = SDL_GetKeyboardState(&m_numkeys);

		m_keystate = new Uint8[m_numkeys];
		m_prevKeystate = new Uint8[m_numkeys];
		
		memcpy(m_keystate, keystate, m_numkeys);
		
		memcpy(m_prevKeystate, keystate, m_numkeys);

		return true;
	}

	void inputSystem::shutdown(){
		delete[] m_keystate;
		delete[] m_prevKeystate;
	}

	void inputSystem::update(){
		memcpy(m_prevKeystate, m_keystate, m_numkeys);
		
		const Uint8* keystate = SDL_GetKeyboardState(&m_numkeys);
		
		memcpy(m_keystate, keystate, m_numkeys);
	}

	inputSystem::eButtonState inputSystem::GetButtonState(int id){
		eButtonState state = eButtonState::IDLE;

		bool buttonDown = GetButtonDown(id);
		bool prevButtonDown = GetPreviousButtonDown(id);

		if (buttonDown) {
			state = (prevButtonDown) ? eButtonState::HELD : eButtonState::PRESSED ;
		}
		else {
			state = (prevButtonDown) ? eButtonState::RELEASED : eButtonState::IDLE ;
		}

		return state;
	}

	bool inputSystem::GetButtonDown(int id){
		return m_keystate[id];
	}

	bool AZ::inputSystem::GetPreviousButtonDown(int id){
		return m_prevKeystate[id];
	}
}
