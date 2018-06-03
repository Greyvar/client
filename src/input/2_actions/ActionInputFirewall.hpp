#include <chrono>

using namespace std;
using namespace std::chrono;

/**
This class implements;

- input rate limiting
- input semaphores

*/
class ActionInputFirewall {
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

} actionInputFirewall;

