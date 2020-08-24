
#include "pch.h"
#include "framework.h"
#include "Engine.h"

namespace AZ {
	bool engine::startup(){
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return false;
		}

		m_systems.push_back(new renderer);
		m_systems.push_back(new inputSystem);
		m_systems.push_back(new resourceManager);

		for(auto system : m_systems) {
			system->startup();
		}

		getSystem<renderer>()->createWindow("Higher on the streets, and I know it's my time to go", 800, 600);

		return true;
	}

	void engine::shutdown(){
		for (auto system : m_systems) {
			system->startup();
			delete system;
		}
		m_systems.clear();

		SDL_Quit();
	}

	void engine::update(){
		m_timer.tick();
		for (auto system : m_systems) {
			system->update();
		}
	}
}
