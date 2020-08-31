#pragma once
#include "pch.h"
#include "Graphics/Renderer.h"
#include "Resource/ResourceManager.h"
#include "Input/Input.h"
#include "Core/Timer.h"
#include "Physics/PhysicsSystem.h"
#include "Audio/AudioSystem.h"

namespace AZ {
	class system;

	class engine {
	public:
		bool startup();
		void shutdown();
		void update();

		AZ::frameTimer& getTimer() { return m_timer; }

		template<typename T>
		T* getSystem();

	protected:
		std::vector<system*> m_systems;
		AZ::frameTimer m_timer;
	};

	template<typename T>
	inline T* engine::getSystem() {
		T* result{ nullptr };
		for (auto system : m_systems) {
			result = dynamic_cast<T*>(system);
			if (result) break;
		}

		return result;
	}
}