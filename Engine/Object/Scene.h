#pragma once
#include "Object.h"
#include <list>

namespace AZ {
	class engine;
	class gameObject;

	class scene : public object {
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;

		void read(const rapidjson::Value& value) override;
		void readGameObjects(const rapidjson::Value& value);
		void readPrototypes(const rapidjson::Value& value);

		void update() override;
		void draw();

		gameObject* find(const std::string& name);

		void addGameObject(gameObject* gameObject);
		void removeGameObject(gameObject* gameObject);
		void removeAllGameObjects();

	protected:
		engine* m_engine{ nullptr };
		std::list<gameObject*> m_gameObjects;
	};
}