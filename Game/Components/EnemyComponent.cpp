#include "pch.h"
#include "EnemyComponent.h"
#include "Object/GameObject.h"
#include "Object/Scene.h"
#include "Components/PhysicsComponent.h"

bool AZ::enemyComponent::create(void* data){
	m_owner = static_cast<gameObject*>(data);

	return false;
}

void AZ::enemyComponent::destroy(){
}

void AZ::enemyComponent::update(){
	gameObject* player = m_owner->m_scene->find("Player");
	if (player) {
		Vector2 direction = player->m_transform.position - m_owner->m_transform.position;
		Vector2 force = direction.normalized() * 10.0f;

		physicsComponent* physicsComponent = m_owner->getComponent<AZ::physicsComponent>();
		physicsComponent->applyForce(force);
	}
}
