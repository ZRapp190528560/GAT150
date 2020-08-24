#pragma once
#include "Object/Object.h"
#include "Object/GameObject.h"

namespace AZ {
	class gameObject;

	class component : public object {
	public:
		virtual void update() = 0;

		friend class gameObject;

	protected:
		gameObject* m_owner{ nullptr };
	};
}