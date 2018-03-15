#include <iostream>

#include "Renderer.hpp"
#include "GameState.hpp"
#include "startup.hpp"

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
				case SDL_AUDIODEVICEADDED:
					std::cout << "Audio device found" << std::endl;
					break;
				default: 
					std::cout << "Unknown event: " << e.type << std::endl;
			}
		}

		Renderer::get().renderFrame();

		SDL_Delay(100);
	}
}

void initLibraries() {
	SDL_Init(SDL_INIT_EVERYTHING);

	initControllerJoysticks();

	initFreetype();
}

int main(int argc, char* argv[]) {
	initLibraries();

	SDL_Window *win = SDL_CreateWindow("Greyvar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 512, SDL_WINDOW_SHOWN);
	SDL_SetWindowResizable(win, SDL_TRUE);

	Renderer::set(win, SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
//	Renderer::get().resCache->loadStartup();

	GameState::get().loadWorld("default");

	mainLoop();

	SDL_Quit();

	return 0;
}

