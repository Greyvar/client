#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <map>

#include "components/MenuItem.hpp"

#include "layout/LayoutManager.hpp"

#include "screens/ScreenMainMenu.hpp"
#include "screens/ScreenServerBrowser.hpp"
#include "screens/ScreenConsole.hpp"

#include "../Scene.hpp"
#include "../common.hpp"

using namespace std;

void startGame();

class Gui {
	public:
		Gui();

		ScreenMainMenu* screenMainMenu = new ScreenMainMenu();
		ScreenConsole* screenConsole = new ScreenConsole();

		Screen* currentScreen = screenMainMenu;

		Scene scene = MENU;

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

		void onWindowResized() {
			this->layoutManager->doLayout(this->currentScreen);
		}

		std::map<std::chrono::_V2::system_clock::time_point, string> messages;
	private:
		LayoutManager* layoutManager = new LayoutManager();
};

