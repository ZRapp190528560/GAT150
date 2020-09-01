#pragma once
#include "Components/Component.h"

namespace AZ {
	class playerComponent : public component {
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual object* clone() const override { return new playerComponent(*this); }

		virtual void update() override;

		void collisionEnter(const AZ::event& event);
		void collisionExit(const AZ::event& event);
	};
}