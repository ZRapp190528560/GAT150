#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"

namespace AZ {
	bool AZ::playerComponent::create(void* data){
		m_owner = static_cast<gameObject*>(data);
		return true;
	}

	void AZ::playerComponent::destroy(){
	}

	void AZ::playerComponent::update() {
		if (m_owner->m_engine->getSystem<AZ::inputSystem>()->GetButtonState(SDL_SCANCODE_A) == AZ::inputSystem::eButtonState::HELD) {
			m_owner->m_transform.angle = m_owner->m_transform.angle - 270.0f * m_owner->m_engine->getTimer().deltaTime();
		}
		if (m_owner->m_engine->getSystem<AZ::inputSystem>()->GetButtonState(SDL_SCANCODE_D) == AZ::inputSystem::eButtonState::HELD) {
			m_owner->m_transform.angle = m_owner->m_transform.angle + 270.0f * m_owner->m_engine->getTimer().deltaTime();
		}

		AZ::Vector2 force{ 0,0 };
		if (m_owner->m_engine->getSystem<AZ::inputSystem>()->GetButtonState(SDL_SCANCODE_W) == AZ::inputSystem::eButtonState::HELD) {
			force = AZ::Vector2::forward * 1000.0f;
		}
		force = AZ::Vector2::rotate(force, AZ::Math::deg_to_rad(m_owner->m_transform.angle));

		physicsComponent* component = m_owner->getComponent<physicsComponent>();
		if (component) {
			component->applyForce(force);
		}
	}
}
