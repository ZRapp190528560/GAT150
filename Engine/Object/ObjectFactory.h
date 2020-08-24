#pragma once
#include "Core/factory.h"
#include "Core/Singleton.h"
#include "Object.h"

namespace AZ {
	class objectFactoryImpl : public factory<object, std::string> {
	public:
		void initialize();
	};
	class objectFactory : public singleton<objectFactoryImpl> {
	private:
		objectFactory() {}
	};
}