#pragma once
#include "Core/System.h"
#include "Resource/resource.h"
#include <map>

namespace AZ {
	class resourceManager : public system {
	public:
		virtual bool startup() override;
		virtual void shutdown() override;
		virtual void update() override;

		template<typename T>
		T* get(const std::string& name, void* data = nullptr);

		void removeAll();

	protected:
		std::map<std::string, resource*> m_resources;
	};

	template<typename T>
	inline T* resourceManager::get(const std::string& name, void* data)
	{
		T* resource = dynamic_cast<T*>(m_resources[name]);

		if (!resource) {
			resource = new T;
			resource->create(name, data);

			m_resources[name] = resource;
		}


		return resource;
	}
}