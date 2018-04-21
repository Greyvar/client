#include "input/1_bindings/common.hpp"

#include <list>
#include <algorithm>

#include "../PlayerInput.hpp"
#include "GameState.hpp"
#include "common.hpp"
#include "cvars.hpp"

using namespace std;

list<HidInput> keysThatArePressed;

void resetKeyboard() {
}

void recvKeyupInput(SDL_Event e) {
	keysThatArePressed.remove((HidInput) e.key.keysym.scancode);
}

void recvKeydownInput(SDL_Event e) {
	if (find(keysThatArePressed.begin(), keysThatArePressed.end(), (HidInput) e.key.keysym.scancode) == keysThatArePressed.end()) {
		keysThatArePressed.push_back((HidInput) e.key.keysym.scancode);
	}
}

/*
 * This function basically implements key-repeat on every frame until we hear
 * that the key is unpressed.
 *
 * This means we don't have to worry about user's preferences for keyboard input,
 * and can still use the SDL event system for keys instead of directly polling 
 * they keyboard and checking every key.
 *
 * Discarding input is done in the action layer.
 */
void recvKeyboardInput() {
	LocalPlayer* lp = GameState::get().getFirstLocalPlayer();

	if (cvarGetb("bind_keyboard")) {
		for (HidInput key : keysThatArePressed) {
			new PlayerInput(lp, key);
		}
	}

	if (cvarGetb("debug_keys")) {
		cout << "num keys: " << keysThatArePressed.size() << endl;

		for (auto a : keysThatArePressed) {
			cout << a << endl;
		}
	}
}
