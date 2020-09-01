#pragma once
#include "Components/Component.h"

namespace AZ {
	class enemyComponent : public component {
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual object* clone() const override { return new enemyComponent(*this); }

		virtual void update() override;
	};
}