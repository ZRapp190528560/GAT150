#include "pch.h"
#include "ResourceManager.h"

namespace AZ {
	bool resourceManager::startup() {
		return true;
	}

	void resourceManager::shutdown(){
		removeAll();
	}

	void resourceManager::update(){
	}

	void resourceManager::removeAll() {
		for (auto resource : m_resources) {
			resource.second->destroy();
			delete resource.second;
		}

		m_resources.clear();
	}
}
