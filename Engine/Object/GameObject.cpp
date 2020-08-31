#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"
#include "Core/factory.h"
#include "Object/ObjectFactory.h"

AZ::gameObject::gameObject(const gameObject& other){
	m_name = other.m_name;
	m_tag = other.m_tag;
	m_lifetime = other.m_lifetime;

	m_flags = other.m_flags;

	m_transform = other.m_transform;
	m_engine = other.m_engine;

	for (component* component : other.m_components) {
		AZ::component* clone = dynamic_cast<AZ::component*>(component->clone());
		clone->m_owner = this;
		addComponent(clone);
	}
}

bool AZ::gameObject::create(void* data){
	m_engine = static_cast<engine*>(data);

	return true;
}

void AZ::gameObject::destroy(){
	removeAllComponents();
}

void AZ::gameObject::read(const rapidjson::Value& value){
	json::Get(value, "name", m_name);
	json::Get(value, "tag", m_tag);
	json::Get(value, "lifetime", m_lifetime);

	bool transient = m_flags[eFlags::TRANSIENT];
	json::Get(value, "transient", transient);
	m_flags[eFlags::TRANSIENT] = transient;

	AZ::json::Get(value, "position", m_transform.position);
	AZ::json::Get(value, "scale", m_transform.scale);
	AZ::json::Get(value, "angle", m_transform.angle);

	if (value.HasMember("Components")) {
		const rapidjson::Value& componentsValue = value["Components"];
		if (componentsValue.IsArray()){
			readComponents(componentsValue);
		}
	}
}

void AZ::gameObject::readComponents(const rapidjson::Value& value) {
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& componentValue = value[i];
		if (componentValue.IsObject()) {
			std::string typeName;
			AZ::json::Get(componentValue, "type", typeName);

			AZ::component* component = AZ::objectFactory::instance().create<AZ::component>(typeName);
			if (component){
				component->create(this);
				component->read(componentValue);
				addComponent(component);
			}
		}
	}
}


void AZ::gameObject::update(){
	for (auto component : m_components) {
		component->update();
	}

	if (m_flags[eFlags::TRANSIENT]) {
		m_lifetime -= m_engine->getTimer().deltaTime();
		m_flags[eFlags::DESTROY] = (m_lifetime <= 0);
	}
}

void AZ::gameObject::draw(){
	renderComponent* component = getComponent<renderComponent>();
	if (component) {
		component->draw();
	}
}

void AZ::gameObject::beginContact(gameObject* otherObject){
	m_contacts.push_back(otherObject);
}

void AZ::gameObject::endContact(gameObject* otherObject){
	m_contacts.remove(otherObject);
}

std::vector<AZ::gameObject*> AZ::gameObject::getContactsWithTag(const std::string& tag){
	std::vector<AZ::gameObject*> contacts;

	for (auto contact : m_contacts) {
		if (contact->m_tag == tag) {
			contacts.push_back(contact);
		}
	}

	return contacts;
}

void AZ::gameObject::addComponent(component* comp){
	m_components.push_back(comp);
}

void AZ::gameObject::removeComponent(component* comp){
	auto iter = std::find(m_components.begin(), m_components.end(), comp);
	if (iter != m_components.end()) {
		(*iter)->destroy();
		delete (*iter);
	}
}

void AZ::gameObject::removeAllComponents(){
	for (auto component : m_components) {
		component->destroy();
		delete component;
	}
	m_components.clear();
}
