#include "pch.h"
#include "Texture.h"
#include "Math/Math.h"
#include "Engine.h"
#include "Object/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"
#include "Core/Json.h"
#include "Object/ObjectFactory.h"
#include "Object/Scene.h"
#include "TileMap.h"

AZ::engine engine;
AZ::scene scene;

int main(int, char**){
	engine.startup();

	scene.create(&engine);

	AZ::objectFactory::instance().initialize();
	AZ::objectFactory::instance().f_register("PlayerComponent", new AZ::creator<AZ::playerComponent, AZ::object>);
	AZ::objectFactory::instance().f_register("EnemyComponent", new AZ::creator<AZ::enemyComponent, AZ::object>);

	rapidjson::Document document;
	AZ::json::Load("scene.txt", document);
	scene.read(document);

	AZ::tileMap tileMap;
	AZ::json::Load("TileMap.txt", document);
	tileMap.read(document);
	tileMap.create(&scene);

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		engine.update();
		scene.update();

		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		}

		if (engine.getSystem<AZ::inputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == AZ::inputSystem::eButtonState::PRESSED) {
			quit = true;
		}

		engine.getSystem<AZ::renderer>()->beginFrame();

		scene.draw();

		engine.getSystem<AZ::renderer>()->endFrame();
	}

	scene.destroy();
	engine.shutdown();

	return 0;
}

