#pragma once
#include "Core/System.h"
#include "box2d/box2d.h"
#include "Object/GameObject.h"

namespace AZ {
	class physicsSystem : public system {
	public:
		struct rigidBodyData {
			Vector2 size;
			float density{ 0 };
			float friction{ 1 };
			float restitution{ 0.3f };
			bool fixRotate{ false };
			bool isDynamic{ false };
			bool isSensor{ false };
		};
	public:
		virtual bool startup() override;
		virtual void shutdown() override;
		virtual void update() override;

		b2Body* createBody(const Vector2& position, float angle, const rigidBodyData& data, class gameObject* gameObject);
		void destroyBody(b2Body* body);

		static Vector2 worldToScreen(const Vector2& world) { return world * 32.0f; }
		static Vector2 screenToWorld(const Vector2& screen) { return screen / 32.0f; }

	protected:
		b2World* m_world{ nullptr };
		class contactListener* m_listener{ nullptr };
	};
}