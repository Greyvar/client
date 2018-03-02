#include <iostream>

#include "Renderer.hpp"
#include "GameState.hpp"

Entity* getPlayer(int p) {
	return GameState::get().world->entityGrid->entities.at(p);
}

void handleKeypress(SDL_KeyboardEvent key) {
	const int speed = 4;

	switch (key.keysym.sym) {
		case SDLK_ESCAPE:
			std::cout << "escapppppe" << std::endl;

			SDL_Event quitEvent;
			quitEvent.type = SDL_QUIT;

			SDL_PushEvent(&quitEvent);
			break;
		case SDLK_w:
			getPlayer(0)->pos->y -= speed;
			break;
		case SDLK_s:
			getPlayer(0)->pos->y += speed;
			break;
		case SDLK_a:
			getPlayer(0)->pos->x -= speed;
			break;
		case SDLK_d:
			getPlayer(0)->pos->x += speed;
			break;
		default:
			std::cout << key.keysym.sym << std::endl;
	}
}

void handleControllerAxis(SDL_ControllerAxisEvent e) {
	switch (e.which) {
		case SDL_CONTROLLER_BUTTON_LEFTSTICK:
		case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
			cout << "controller " << e.axis << ":" << e.value << endl;
	}
}

void handleControllerButton(SDL_ControllerButtonEvent e) {
	switch (e.button) {
	}
}

void initControllers() {
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			SDL_GameController *controller = SDL_GameControllerOpen(i);

			if (!controller) {
				std::cout << "Could not open controller: " << i << std::endl;
			} else {
				std::cout << "Found controller: " << i << std::endl;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);

	initControllers();

	SDL_Window *win = SDL_CreateWindow("Greyvar", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	Renderer::set(SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

	GameState::get().loadWorld("default");

	SDL_Event e;

	while (true) {
		std::cout << "loop" << std::endl;

		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					goto completedMainLoop;
				case SDL_CONTROLLERAXISMOTION:
					//handleControllerAxis(e.value);
					break;
				case SDL_KEYDOWN:
					handleKeypress(e.key);
					break;
				default: 
					std::cout << "Unknown event: " << e.type << std::endl;
			}
		}

		Renderer::get().renderFrame();

		SDL_Delay(100);
	}

	completedMainLoop: SDL_Quit();

	return 0;
}

