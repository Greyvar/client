#pragma once

#include <iostream>
#include <vector>

#include "common.hpp"

using namespace std;

enum UserInterfaceState {
	PLAY,
	MENU,
	CONSOLE
};

typedef void (*MenuItemAction)(void);

void quitGame();
void startGame();

class MenuItem {
	public:
		MenuItem(std::string text, MenuItemAction action) {
			this->text = text;
			this->action = action;
		}

		std::string text;
		MenuItemAction action;
};

class UserInterface {
	public:
		UserInterface() {
			this->setupMainMenu();
		}

		std::vector<string> consoleHistory; 

		std::vector<MenuItem*> mainMenu;

		std::vector<MenuItem*>* currentMenu;

		unsigned int currentlySelectedMenuItem = 0;

		std::string subtitle; 

		UserInterfaceState state = MENU;

		void setupMainMenu();

		void executeCurrentMenuItem() {
			playSound("interface/interface3.wav", UI);

			MenuItem* item = this->currentMenu->at(this->currentlySelectedMenuItem);

			item->action();
		}

		void selectPrevMenuItem() {
			if (this->currentlySelectedMenuItem > 0) {
				this->currentlySelectedMenuItem--;

				playSound("interface/interface1.wav", UI);
			} else {
				playSound("interface/interface2.wav", UI);
			}
		}

		void selectNextMenuItem() {
			if (this->currentlySelectedMenuItem < this->currentMenu->size() - 1) {
				this->currentlySelectedMenuItem++;

				playSound("interface/interface1.wav", UI);
			} else {
				playSound("interface/interface2.wav", UI);
			}
		}

		void toggleConsole();

		void toggleMenu() {
			playSound("interface/interface3.wav", UI);

			if (this->state == MENU) {
				this->state = PLAY;
			} else {
				this->state = MENU;
			}
		}
};

enum TextAlignment {
	LEFT,
	CENTER
};
