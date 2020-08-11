#include "pch.h"
#include "Texture.h"
#include "Graphics/Renderer.h"
#include "Resource/ResourceManager.h"
#include "Core/Timer.h"
#include "Input/Input.h"

AZ::resourceManager resourceManager;
AZ::renderer renderer;
AZ::inputSystem inputSystem;

AZ::frameTimer timer;

int main(int, char**)
{
	renderer.startup();
	renderer.createWindow("GAT150", 800, 600);
	inputSystem.startup();

	AZ::texture* swords = resourceManager.get<AZ::texture>("MH4-Long_Sword_Render_039.png", &renderer);
	AZ::texture* background = resourceManager.get<AZ::texture>("background.png", &renderer);

	float angle{ 0 };
	AZ::Vector2 position{ 400, 300 };

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		inputSystem.update();

		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		default:
			break;
		}

		timer.tick();

		renderer.beginFrame();

		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == AZ::inputSystem::eButtonState::HELD){
			position.x = position.x - 200.0f * timer.deltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == AZ::inputSystem::eButtonState::HELD){
			position.x = position.x + 200.0f * timer.deltaTime();
		}

		angle += 45.0f;
		background->draw({ 0, 0 }, { 1, 1 }, 0);
		swords->draw( position, { 0.7f, 0.7f }, angle);
		swords->draw({ 500, 300 }, { 0.7f, 0.7f }, angle + 70);

		renderer.endFrame();
	}

	renderer.shutdown();
	inputSystem.shutdown();
	SDL_Quit();

	return 0;
}

