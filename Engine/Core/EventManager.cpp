#include "pch.h"
#include "EventManager.h"

void AZ::eventManager::subscribe(const std::string type, function_t function, object* owner){
	observer t_observer;

	t_observer.function = function;
	t_observer.owner = owner;

	m_observers[type].push_back(t_observer);
}

void AZ::eventManager::notify(const AZ::event& event){
	auto observers = m_observers[event.type];
	for (auto t_observer : observers) {
		if (event.receiver == nullptr || event.receiver == t_observer.owner) {
			t_observer.function(event);
		}
	}
}
