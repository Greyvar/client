#include <iostream>

#include "Renderer.hpp"
#include "GameState.hpp"

void handleKeypress(SDL_KeyboardEvent key);

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

void mainLoop() {
	SDL_Event e;

	while (true) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_WINDOWEVENT:
					SDL_GetWindowSize(Renderer::get().getWindow(), &Renderer::get().window_w, &Renderer::get().window_h);
					cout << "window changed" << endl;
					break;
				case SDL_QUIT:
					return;
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
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);

	initControllers();

	SDL_Window *win = SDL_CreateWindow("Greyvar", 100, 100, 640, 512, SDL_WINDOW_SHOWN);
	SDL_SetWindowResizable(win, SDL_TRUE);

	Renderer::set(win, SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

	GameState::get().loadWorld("default");

	mainLoop();

	SDL_Quit();

	return 0;
}

