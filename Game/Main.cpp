#include "pch.h"
#include "Texture.h"
#include "Math/Math.h"
#include "Engine.h"
#include "Object/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Object/ObjectFactory.h"
#include "Object/Scene.h"

AZ::engine engine;
AZ::scene scene;

int main(int, char**){
	engine.startup();

	scene.create(&engine);

	AZ::objectFactory::instance().initialize();
	AZ::objectFactory::instance().f_register("PlayerComponent", new AZ::creator<AZ::playerComponent, AZ::object>);

	rapidjson::Document document;
	AZ::json::Load("scene.txt", document);
	scene.read(document);

	//for (size_t i = 0; i < 10; i++){
	//	AZ::gameObject* gameObject = AZ::objectFactory::instance().create<AZ::gameObject>("ProtoExplosion");
	//	gameObject->m_transform.position = AZ::Vector2{ AZ::random(0, 800), AZ::random(0, 600) };
	//	gameObject->m_transform.angle = AZ::random(0, 360);
	//	scene.addGameObject(gameObject); 
	//}


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

