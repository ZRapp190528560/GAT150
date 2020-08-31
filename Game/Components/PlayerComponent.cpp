#include "pch.h"
#include "PlayerComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/AudioComponent.h"

namespace AZ {
	bool AZ::playerComponent::create(void* data){
		m_owner = static_cast<gameObject*>(data);
		return true;
	}

	void AZ::playerComponent::destroy(){
	}

	void AZ::playerComponent::update() {
		auto contacts = m_owner->getContactsWithTag("Floor");
		bool onGround = (!contacts.empty());

		AZ::Vector2 force{ 0,0 };
		if (m_owner->m_engine->getSystem<AZ::inputSystem>()->GetButtonState(SDL_SCANCODE_A) == AZ::inputSystem::eButtonState::HELD) {
			//m_owner->m_transform.angle = m_owner->m_transform.angle - 270.0f * m_owner->m_engine->getTimer().deltaTime();
			force.x = -200;
		}
		if (m_owner->m_engine->getSystem<AZ::inputSystem>()->GetButtonState(SDL_SCANCODE_D) == AZ::inputSystem::eButtonState::HELD) {
			//m_owner->m_transform.angle = m_owner->m_transform.angle + 270.0f * m_owner->m_engine->getTimer().deltaTime();
			force.x = 200;
		}
		if (m_owner->m_engine->getSystem<AZ::inputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == AZ::inputSystem::eButtonState::PRESSED && onGround) {
			force.y = -1500;

			audioComponent* audioComponent = m_owner->getComponent<AZ::audioComponent>();
			if (audioComponent){
				audioComponent->play();
			}
		}

		physicsComponent* component = m_owner->getComponent<physicsComponent>();
		if (component) {
			component->applyForce(force);
		}

		auto coinContacts = m_owner->getContactsWithTag("coin");
		for (gameObject* coin : coinContacts) {
			coin->m_flags[gameObject::eFlags::DESTROY] = true;
		}
	}
}
