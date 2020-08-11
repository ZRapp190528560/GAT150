#pragma once
#include "Core/System.h"

namespace AZ {
	class inputSystem : public system {
	public:
		enum class eButtonState {
			IDLE,
			PRESSED,
			HELD,
			RELEASED
		};
	public:
		virtual bool startup() override;

		virtual void shutdown() override;

		virtual void update() override;

		eButtonState GetButtonState(int id);

		bool GetButtonDown(int id);

		bool GetPreviousButtonDown(int id);

	protected:
		Uint8* m_keystate;
		Uint8* m_prevKeystate;
		int m_numkeys;
	};
}