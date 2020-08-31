#pragma once
#include "Components/PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace AZ {
	class rigidBodyComponent : public physicsComponent {
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual object* clone() const override { return new rigidBodyComponent( *this ); }

		virtual void update() override;

		void read(const rapidjson::Value& value);

		void applyForce(const Vector2& force) override;

	protected:
		b2Body* m_body{ nullptr };
		AZ::physicsSystem::rigidBodyData m_data;
	};
}