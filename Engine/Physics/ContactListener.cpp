#include "pch.h"
#include "ContactListener.h"
#include "Object/GameObject.h"

void AZ::contactListener::BeginContact(b2Contact* contact) {
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (fixtureA->GetUserData() && fixtureB->GetUserData()) {
		gameObject* gameObjectA = static_cast<gameObject*>(fixtureA->GetUserData());
		gameObject* gameObjectB = static_cast<gameObject*>(fixtureB->GetUserData());

		gameObjectA->beginContact(gameObjectB);
		gameObjectB->beginContact(gameObjectA);
	}
}

void AZ::contactListener::EndContact(b2Contact* contact) {
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (fixtureA->GetUserData() && fixtureB->GetUserData()) {
		gameObject* gameObjectA = static_cast<gameObject*>(fixtureA->GetUserData());
		gameObject* gameObjectB = static_cast<gameObject*>(fixtureB->GetUserData());

		gameObjectA->endContact(gameObjectB);
		gameObjectB->endContact(gameObjectA);
	}
}
