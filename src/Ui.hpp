#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <map>

#include "Scene.hpp"
#include "common.hpp"

using namespace std;

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
		chrono::system_clock::time_point lastAnimationTime = chrono::system_clock::now();

		UserInterface() {
			this->setupMainMenu();
		}

		std::vector<string> consoleHistory; 

		std::vector<MenuItem*> mainMenu;

		std::vector<MenuItem*>* currentMenu;

		unsigned int currentlySelectedMenuItem = 0;

		std::string subtitle; 

		Scene scene = MENU;

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

			if (this->scene == MENU) {
				this->scene = PLAY;
			} else {
				this->scene = MENU;
			}
		}

		void addMessage(string message) {
			this->messages[std::chrono::system_clock::now()] = message;
		}

		std::map<std::chrono::_V2::system_clock::time_point, string> messages;
	private:
};

enum TextAlignment {
	LEFT,
	CENTER
};
