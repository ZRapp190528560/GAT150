#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Object/ObjectFactory.h"

namespace AZ {
	bool scene::create(void* data) {
		m_engine = static_cast<engine*>(data);
		return true;
	}

	void scene::destroy() {
		removeAllGameObjects();
	}

	void scene::read(const rapidjson::Value& value){
		if (value.HasMember("Prototypes")) {
			const rapidjson::Value& objectsValue = value["Prototypes"];
			if (objectsValue.IsArray()) {
				readPrototypes(objectsValue);
			}
		}
		if (value.HasMember("GameObjects")) {
			const rapidjson::Value& objectsValue = value["GameObjects"];
			if (objectsValue.IsArray()){
				readGameObjects(objectsValue);
			}
		}
	}


	void scene::readGameObjects(const rapidjson::Value& value) {
		for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject()) {
				std::string typeName;

				AZ::json::Get(objectValue, "type", typeName);
				AZ::gameObject* gameObject = AZ::objectFactory::instance().create<AZ::gameObject>(typeName);

				if (gameObject) {
					gameObject->create(m_engine);
					gameObject->read(objectValue);
					addGameObject(gameObject);
				}
			}
		}
	}

	void scene::readPrototypes(const rapidjson::Value& value){
		for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject()) {
				std::string typeName;

				AZ::json::Get(objectValue, "type", typeName);
				AZ::gameObject* gameObject = AZ::objectFactory::instance().create<AZ::gameObject>(typeName);

				if (gameObject) {
					gameObject->create(m_engine);
					gameObject->read(objectValue);
				
					objectFactory::instance().f_register(gameObject->m_name, new prototype<object>(gameObject));
				}
			}
		}
	}

	void scene::update() {
		for (auto gameObject : m_gameObjects) {
			gameObject->update();
		}
	}

	void scene::draw() {
		for (auto gameObject : m_gameObjects) {
			gameObject->draw();
		}
	}

	gameObject* scene::find(const std::string& name){
		for (auto gameObject : m_gameObjects){
			if (gameObject->m_name == name) {
				return gameObject;
			}
		}

		return nullptr;
	}

	void scene::addGameObject(gameObject* gameObject) {
		m_gameObjects.push_back(gameObject);
	}

	void scene::removeGameObject(gameObject* gameObject) {
		auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
		if (iter != m_gameObjects.end()) {
			(*iter)->destroy();
			delete (*iter);
			m_gameObjects.erase(iter);
		}
	}

	void scene::removeAllGameObjects() {
		for (gameObject* gameObject : m_gameObjects) {
			gameObject->destroy();
			delete gameObject;
		}

		m_gameObjects.clear();
	}
}