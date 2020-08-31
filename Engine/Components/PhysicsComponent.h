#pragma once
#include "Component.h"
#include "Math/Vector2.h"

namespace AZ {
	class physicsComponent : public component {
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual object* clone() const override { return new physicsComponent(*this); }

		virtual void update() override;

		virtual void applyForce(const Vector2& force) { m_force = force; }
		virtual Vector2& getVelocity() { return m_velocity; }

	protected:
		Vector2 m_velocity;
		Vector2 m_force;
		float m_drag{ 1 };
	};
}