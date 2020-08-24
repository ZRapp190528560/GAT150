#pragma once
#include "Component.h"

namespace AZ {
	class renderComponent : public component {
	public:
		virtual void draw() = 0;
	};
}