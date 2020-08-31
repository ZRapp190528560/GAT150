#include "pch.h"
#include "PhysicsSystem.h"
#include "ContactListener.h"

bool AZ::physicsSystem::startup() {
	b2Vec2 gravity{ 0, 10 };
	m_world = new b2World(gravity);

	m_listener = new contactListener;
	m_world->SetContactListener(m_listener);

	return true;
}

void AZ::physicsSystem::shutdown() {
	delete m_world;
	m_world = nullptr;
}

void AZ::physicsSystem::update() {
	float timestep = 0.0166f;
	m_world->Step(timestep, 8, 3);
}

b2Body* AZ::physicsSystem::createBody(const Vector2& position, float angle, const rigidBodyData& data, class AZ::gameObject* gameObject) {
	b2BodyDef bodyDef;

	Vector2 world = physicsSystem::screenToWorld(position);

	bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;
	bodyDef.position.Set(world.x, world.y);
	bodyDef.angle = AZ::Math::deg_to_rad(angle);
	bodyDef.fixedRotation = data.fixRotate;
	b2Body* body = m_world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	Vector2 worldSize = physicsSystem::screenToWorld(data.size);
	shape.SetAsBox(worldSize.x, worldSize.y);

	b2FixtureDef fixtureDef;
	fixtureDef.density = data.density;
	fixtureDef.friction = data.friction;
	fixtureDef.restitution = data.restitution;
	fixtureDef.isSensor = data.isSensor;
	fixtureDef.shape = &shape;
	fixtureDef.userData = gameObject;

	body->CreateFixture(&fixtureDef);

	return body;
}

void AZ::physicsSystem::destroyBody(b2Body* body) {
	m_world->DestroyBody(body);
}
