#include "pch.h"
#include "SpriteComponent.h"
#include "Texture.h"

bool AZ::spriteComponent::create(void* data) {
	m_owner = static_cast<gameObject*>(data);
	return true;
}

void AZ::spriteComponent::destroy() {

}

void AZ::spriteComponent::read(const rapidjson::Value& value){
	AZ::json::Get(value, "texture", m_textureName);
	AZ::json::Get(value, "origin", m_origin);
	AZ::json::Get(value, "rect", m_rect);
}

void AZ::spriteComponent::update(){

}

void AZ::spriteComponent::draw(){
	texture* texture = m_owner->m_engine->getSystem<AZ::resourceManager>()->get<AZ::texture>(m_textureName, m_owner->m_engine->getSystem<AZ::renderer>());
	texture->draw(m_rect, m_owner->m_transform.position, m_owner->m_transform.angle, AZ::Vector2{ 1.0f, 1.0f } * m_owner->m_transform.scale, m_origin, m_flip);
}
