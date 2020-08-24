#pragma once
#include "Components/Component.h"

namespace AZ {
	class playerComponent : public component {
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual object* clone() override { return new playerComponent(*this); }

		virtual void update() override;
	};
}