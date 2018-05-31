#include <queue>

#include <iostream>
#include <SDL2/SDL.h>
#include <chrono>

#include "NetworkManager.hpp"
#include "../PlayerInput.hpp"
#include "common.hpp"
#include "cvars.hpp"
#include "GameState.hpp"
#include "NetworkManager.hpp"

using namespace std;
using namespace std::chrono;

queue<PlayerInput*> boundPlayerInputQueue;

/**
This class implements;

- input rate limiting
- input semaphores

*/
class InputFirewall {
	public:
	bool canDo(ActionInput ai) {
		ActionInputType ait = this->getActionInputType(ai);

		switch (ait) {
			case USE_MENU: return this->canUseMenu();
			case WALK: return this->canWalk();
			case OTHER: return true;
		}

		cout << "canDo() - ait not checked: " << ait << endl;

		return false;
	}

	private:
	ActionInputType getActionInputType(ActionInput ai) {
		if (ai >= WALK_LEFT && ai <= WALK_DOWN) {
			return WALK;
		} else if (ai >= MENU_UP && ai <= MENU_ITEM_SELECT) {
			return USE_MENU;
		}

		cout << "unclassified type for input action: " << ai << endl;

		return OTHER;
	}

	bool canWalk() {
		if (NetworkManager::get().waitingForMove) {
			return false;
		} else {
			return true;
		}
	}

	system_clock::time_point nextMenuAction = system_clock::now();

	bool canUseMenu() {
		if (system_clock::now() > nextMenuAction) {
			nextMenuAction = system_clock::now() + milliseconds(350);
			return true;
		} else {
			return false;
		}
	}

} inputFirewall;

void executeSinglePlayerInput(PlayerInput* pi) {
	if (cvarGetb("debug_playerinput")) {
		cout << "pi executeAction " << pi << endl;
	}

	if (inputFirewall.canDo(pi->actionInput)) {
		switch (pi->actionInput) {
			case MENU_DOWN:
				GameState::get().ui->selectNextMenuItem();
				break;
			case MENU_UP:
				GameState::get().ui->selectPrevMenuItem();
				break;
			case MENU_ITEM_SELECT:
				GameState::get().ui->executeCurrentMenuItem();
				break;
			case MENU_SHOW:
				GameState::get().ui->scene = MENU;
				break;
			case WALK_UP:
				NetworkManager::get().sendMovr(0, -1);
				break;
			case WALK_DOWN:
				NetworkManager::get().sendMovr(0, 1);
				break;
			case WALK_LEFT:
				NetworkManager::get().sendMovr(-1, 0);
				break;
			case WALK_RIGHT:
				NetworkManager::get().sendMovr(1, 0);
				break;
			case QUIT:
				SDL_Event e;
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
				break;
			default:
				cout << "Unhandled input action: " << pi << endl;
		}
	} else {
		cout << "can't do action " << pi->actionInput << endl;
	}
}

void executeActionInputs() {
	while (!boundPlayerInputQueue.empty()) {
		PlayerInput* pi = boundPlayerInputQueue.front();
	
		executeSinglePlayerInput(pi);

		//actionExecutables(pi->actionInput)();

		boundPlayerInputQueue.pop();

		delete(pi);
	}

}
