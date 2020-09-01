#include "pch.h"
#include "PlayerComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SpriteComponent.h"
#include "Core/EventManager.h"

namespace AZ {
	bool AZ::playerComponent::create(void* data){
		m_owner = static_cast<gameObject*>(data);

		eventManager::instance().subscribe("CollisionEnter", std::bind(&playerComponent::collisionEnter, this, std::placeholders::_1), m_owner);
		eventManager::instance().subscribe("CollisionExit", std::bind(&playerComponent::collisionExit, this, std::placeholders::_1), m_owner);
		return true;
	}

	void AZ::playerComponent::destroy(){
	}

	void AZ::playerComponent::update() {
		auto contacts = m_owner->getContactsWithTag("Floor");
		bool onGround = (!contacts.empty());

		AZ::Vector2 force{ 0,0 };
		if (m_owner->m_engine->getSystem<AZ::inputSystem>()->GetButtonState(SDL_SCANCODE_A) == AZ::inputSystem::eButtonState::HELD) {
			force.x = -200;
		}
		if (m_owner->m_engine->getSystem<AZ::inputSystem>()->GetButtonState(SDL_SCANCODE_D) == AZ::inputSystem::eButtonState::HELD) {
			force.x = 200;
		}
		if (m_owner->m_engine->getSystem<AZ::inputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == AZ::inputSystem::eButtonState::PRESSED && onGround) {
			force.y = -1500;

			audioComponent* audioComponent = m_owner->getComponent<AZ::audioComponent>();
			if (audioComponent){
				audioComponent->setSoundName("Sounds/Jump.wav");
				audioComponent->play();
			}
		}

		physicsComponent* component = m_owner->getComponent<physicsComponent>();
		if (component) {
			component->applyForce(force);

			Vector2 velocity = component->getVelocity();

			spriteComponent* spriteComponent = m_owner->getComponent<AZ::spriteComponent>();
			if (spriteComponent) {
				if (velocity.x < -0.5) spriteComponent->flip(true);
				if (velocity.x > 0.5) spriteComponent->flip(false);
			}
		}
	}

	void playerComponent::collisionEnter(const AZ::event& event){
		gameObject* t_gameObject = dynamic_cast<gameObject*>(event.sender);

		if (t_gameObject->m_tag == "enemy") {
			audioComponent* t_audioComponent = m_owner->getComponent<audioComponent>();
			t_audioComponent->setSoundName("Sounds/death.wav");
			t_audioComponent->play();
		}
		if (t_gameObject->m_tag == "Coin") {
			audioComponent* t_audioComponent = m_owner->getComponent<audioComponent>();
			t_audioComponent->setSoundName("Sounds/Pickup_coin.wav");
			t_audioComponent->play();

			t_gameObject->m_flags[gameObject::eFlags::DESTROY] = true;
		}

		std::cout << "collision enter" << t_gameObject->m_name << std::endl;
	}

	void playerComponent::collisionExit(const AZ::event& event){
		gameObject* t_gameObject = dynamic_cast<gameObject*>(event.sender);


		std::cout << "collision exit" << t_gameObject->m_name << std::endl;
	}
}
