#pragma once
#include "Singleton.h"
#include <string>
#include <map>
#include <list>
#include <functional>

namespace AZ {
	class object;

	struct event {
		std::string type;
		object* sender;
		object* receiver;
		void* data;
	};

	class eventManager : public singleton<eventManager> {
	public:
		using function_t = std::function<void(const AZ::event&)>;

		struct observer {
			function_t function;
			object* owner{ nullptr };
		};

	public:
		void subscribe(const std::string type, function_t function, object* owner = nullptr);
		void notify(const AZ::event& event);

	private:
		std::map<std::string, std::list<observer>> m_observers;
	};
}