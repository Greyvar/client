#include <iostream>
#include <SDL2/SDL.h>
#include <map>

#include "../PlayerInput.hpp"
#include "LocalPlayer.hpp"

using namespace std;

map<SDL_GameController*, LocalPlayer*> gamepadsForLocalPlayers; 

const int DEAD_ZONE = 8000;

void handleGamepadAxis(SDL_GameController* controller, LocalPlayer* lp) {
	auto axisX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	auto axisY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

	if (abs(axisX) > DEAD_ZONE) {
		if (axisX > 0) {
			new PlayerInput(lp, GAMEPAD_JOYSTICK_UP);
		} else {
			new PlayerInput(lp, GAMEPAD_JOYSTICK_DOWN);
		}
	} 

	if (abs(axisY) > DEAD_ZONE) {
		if (axisY > 0) {
			new PlayerInput(lp, GAMEPAD_JOYSTICK_RIGHT);
		} else {
			new PlayerInput(lp, GAMEPAD_JOYSTICK_LEFT);
		}
	} 
}

void handleGamepadButtons(SDL_GameController* controller, LocalPlayer* lp) {
//	new PlayerInput(lp, GAMEPAD_X);
}

void reinitGamepads() {
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			SDL_GameController* controller = SDL_GameControllerOpen(i);

			if (!controller) {
				cout << "Could not open controller: " << i << endl;
			} else {
				cout << "Found controller: " << i << endl;

				gamepadsForLocalPlayers[controller] = new LocalPlayer();
			}
		}
	}
}

void recvGamepadInputs() {
	for (auto pair : gamepadsForLocalPlayers) {
		handleGamepadAxis(pair.first, pair.second);
		handleGamepadButtons(pair.first, pair.second);
	}
}


