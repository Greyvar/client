#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

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

void initControllerJoysticks() {
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			SDL_GameController *controller = SDL_GameControllerOpen(i);

			if (!controller) {
				cout << "Could not open controller: " << i << endl;
			} else {
				cout << "Found controller: " << i << endl;
			}
		}
	}
}


