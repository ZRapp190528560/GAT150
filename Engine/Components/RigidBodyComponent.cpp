#include "pch.h"
#include "RigidBodyComponent.h"

bool AZ::rigidBodyComponent::create(void* data){
	m_owner = static_cast<gameObject*>(data);

	return true;
}

void AZ::rigidBodyComponent::destroy(){
	m_owner->m_engine->getSystem<physicsSystem>()->destroyBody(m_body);
}

void AZ::rigidBodyComponent::read(const rapidjson::Value& value) {
	json::Get(value, "isDynamic", m_data.isDynamic);
	json::Get(value, "fixRotate", m_data.fixRotate);
	json::Get(value, "isSensor", m_data.isSensor);
	json::Get(value, "size", m_data.size);
	json::Get(value, "density", m_data.density);
	json::Get(value, "friction", m_data.friction);
	json::Get(value, "restitution", m_data.restitution);
}

void AZ::rigidBodyComponent::update(){
	if (m_body == nullptr) {
		m_body = m_owner->m_engine->getSystem<physicsSystem>()->createBody(m_owner->m_transform.position, m_owner->m_transform.angle, m_data, m_owner);
	}

	m_owner->m_transform.position = physicsSystem::worldToScreen(m_body->GetPosition());
	m_owner->m_transform.angle = AZ::Math::rad_to_deg(m_body->GetAngle());
	/*m_owner->m_transform.position = m_body->GetPosition();
	m_owner->m_transform.angle = m_body->GetAngle();*/

	m_velocity = m_body->GetLinearVelocity();
	m_velocity.x = AZ::Math::Clamp(m_velocity.x, -5.0f, 5.0f);
	m_body->SetLinearVelocity(m_velocity);
}

void AZ::rigidBodyComponent::applyForce(const Vector2& force) {
	m_body->SetGravityScale(2.0f);
	m_body->ApplyForceToCenter(force, true);
	//m_body->SetLinearDamping(0.2f);
}
