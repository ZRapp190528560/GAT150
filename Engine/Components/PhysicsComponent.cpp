#include "pch.h"
#include "Object/GameObject.h"
#include "PhysicsComponent.h"

bool AZ::physicsComponent::create(void* data){
	m_owner = static_cast<gameObject*>(data);
	m_drag = 0.97f;

	return true;
}

void AZ::physicsComponent::destroy(){
}

void AZ::physicsComponent::update() {
	m_velocity = m_velocity + m_force * m_owner->m_engine->getTimer().deltaTime();
	m_velocity *= m_drag;
	m_owner->m_transform.position = m_owner->m_transform.position + m_velocity * m_owner->m_engine->getTimer().deltaTime();
}
