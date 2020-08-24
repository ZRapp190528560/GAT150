#pragma once
#include "Core/Json.h"

namespace AZ {
	class object {
	public:
		virtual bool create(void* data = nullptr) = 0;
		virtual void destroy() = 0;
		virtual object* clone() { return nullptr; }

		virtual void update() = 0;

		virtual void read(const rapidjson::Value& value) {}

		template<typename T>
		static object* instantiate() {
			T* instance = new T;
			return instance;
		}
	};
}