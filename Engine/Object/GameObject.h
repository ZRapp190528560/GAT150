#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include <vector>

namespace AZ {
	class component;

	class gameObject : public object {
	public:
		gameObject() = default;
		gameObject(const gameObject& other);

		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual object* clone() override { return new gameObject{ *this }; }

		void read(const rapidjson::Value& value) override;
		void readComponents(const rapidjson::Value& value);

		void update();
		void draw();

		template<typename T>
		T* getComponent() {
			T* result{ nullptr };
			for (auto component : m_components) {
				result = dynamic_cast<T*>(component);
				if (result) break;
			}

			return result;
		}

		void addComponent(component* comp);
		void removeComponent(component* comp);
		void removeAllComponents();

		friend class Component;
		friend class physicsComponent;

	public:
		std::string m_name;
		engine* m_engine;
		Transform m_transform;

	protected:
		std::vector<component*> m_components;
	};
}