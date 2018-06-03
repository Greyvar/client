#include <map>

#include "Scene.hpp"
#include "input/PlayerInput.hpp"
#include "input/0_hid/HidInputGesture.hpp"
#include "input/2_actions/common.hpp"
#include "common.hpp"
#include "Scene.hpp"
#include "GameState.hpp"

using namespace std;

map<Scene, map<HidInputGesture, ActionInput>> inputBindings;

queue<PlayerInput*> unboundPlayerInputQueue;

void inputBind(Scene scene, HidInputGesture hidInputGesture, ActionInput ai ) {
	inputBindings[scene][hidInputGesture] = ai;
}

void defaultInputBindings() {
	inputBind(MENU, KEY_ESCAPE, QUIT);
	inputBind(MENU, KEY_ARROW_UP, MENU_UP);
	inputBind(MENU, KEY_ARROW_DOWN, MENU_DOWN);
	inputBind(MENU, KEY_RETURN, MENU_ITEM_SELECT);

	inputBind(PLAY, KEY_ESCAPE, QUIT);
	inputBind(PLAY, KEY_W, WALK_UP);
	inputBind(PLAY, KEY_S, WALK_DOWN);
	inputBind(PLAY, KEY_A, WALK_LEFT);
	inputBind(PLAY, KEY_D, WALK_RIGHT);
	inputBind(PLAY, KEY_ARROW_LEFT, WALK_LEFT);
	inputBind(PLAY, KEY_ARROW_RIGHT, WALK_RIGHT);
	inputBind(PLAY, KEY_ARROW_UP, WALK_UP);
	inputBind(PLAY, KEY_ARROW_DOWN, WALK_DOWN);
	inputBind(PLAY, KEY_TAB, MENU_SHOW);

	inputBind(PLAY, GAMEPAD_JOYSTICK_LEFT, WALK_LEFT);
	inputBind(PLAY, GAMEPAD_JOYSTICK_RIGHT, WALK_RIGHT);
	inputBind(PLAY, GAMEPAD_JOYSTICK_UP, WALK_UP);
	inputBind(PLAY, GAMEPAD_JOYSTICK_DOWN, WALK_DOWN);
	inputBind(PLAY, GAMEPAD_START, JOIN_GAME);

	inputBind(CONSOLE, KEY_RETURN, MENU_UP);
}

void lookupActionBindingForPlayerInput() {
	while (!unboundPlayerInputQueue.empty()) {
		PlayerInput* pi = unboundPlayerInputQueue.front();

		pi->actionInput = inputBindings[GameState::get().gui->scene][pi->hidInputGesture];

		unboundPlayerInputQueue.pop();

		if (pi->actionInput == AI_NOOP) {
			cout << "unbound input: " << pi << endl;
			delete(pi);
		} else { 
			cout << "bound input: " << pi->hidInputGesture << " to " << pi->actionInput << endl;
			boundPlayerInputQueue.push(pi);
		}
	}
}

