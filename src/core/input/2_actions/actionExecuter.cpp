#include "NetworkManager.hpp"
#include "../PlayerInput.hpp"
#include "common.hpp"
#include "cvars.hpp"
#include "GameState.hpp"
#include "NetworkManager.hpp"
#include "ActionInputFirewall.hpp"
#include "gui/Gui.hpp"

#include <queue>

#include <iostream>
#include <SDL2/SDL.h>


using namespace std;

queue<PlayerInput*> boundPlayerInputQueue;

void executeSinglePlayerInput(PlayerInput* pi) {
	if (cvarGetb("debug_playerinput")) {
		cout << "pi executeAction " << pi << endl;
	}

	if (ActionInputFirewall::canDo(pi->actionInput)) {
		switch (pi->actionInput) {
			case ACTION:
				if (GameState::get().getRemotePlayerCount() == 0) {
					NetworkManager::get().sendHelo(pi->localPlayer);
				}
				break;
			case MENU_DOWN:
				Gui::get().currentScreen->selectNextItem();
				break;
			case MENU_UP:
				Gui::get().currentScreen->selectPrevItem();
				break;
			case MENU_ITEM_SELECT:
				Gui::get().currentScreen->executeCurrentItem();
				break;
			case MENU_SHOW:
				Gui::get().scene = MENU;
				break;
			case MENU_BACK:
				Gui::get().goBack();
				break;
			case MENU_CLICK:
				Gui::get().currentScreen->onClick(pi->pointerX, pi->pointerY);
				break;
			case WALK_UP:
				NetworkManager::get().sendMovr(0, -1, pi->localPlayer->username);
				break;
			case WALK_DOWN:
				NetworkManager::get().sendMovr(0, 1, pi->localPlayer->username);
				break;
			case WALK_LEFT:
				NetworkManager::get().sendMovr(-1, 0, pi->localPlayer->username);
				break;
			case WALK_RIGHT:
				NetworkManager::get().sendMovr(1, 0, pi->localPlayer->username);
				break;
			case JOIN_GAME:
				NetworkManager::get().sendHelo(pi->localPlayer);
				break;
			case QUIT:
				SDL_Event e;
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
				break;
			default:
				cout << "No execution for input action: " << pi << endl;
		}
	} else {
		cout << "can't do action " << pi->actionInput << endl;
	}
}

void executeActionInputs() {
	while (!boundPlayerInputQueue.empty()) {
		PlayerInput* pi = boundPlayerInputQueue.front();
	
		executeSinglePlayerInput(pi);

		boundPlayerInputQueue.pop();

		delete(pi);
	}

}
