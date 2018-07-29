#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <map>

#include "components/MenuItem.hpp"

#include "layout/LayoutManager.hpp"

#include "screens/ScreenDashboard.hpp"
#include "screens/ScreenMainMenu.hpp"
#include "screens/ScreenServerBrowser.hpp"
#include "screens/ScreenConsole.hpp"
#include "screens/ScreenPlayerSetup.hpp"
#include "screens/ScreenAbout.hpp"
#include "screens/ScreenSettings.hpp"

#include "../Scene.hpp"
#include "../common.hpp"

using namespace std;

void startGame();

class Gui {
	public:
		Gui(Gui const&) = delete;
		void operator=(Gui const&) = delete;

		static Gui& get() {
			static Gui instance;

			return instance;
		}

		ScreenMainMenu* screenMainMenu = new ScreenMainMenu();
		ScreenConsole* screenConsole = new ScreenConsole();
		ScreenPlayerSetup* screenPlayerSetup = new ScreenPlayerSetup();
		ScreenAbout* screenAbout = new ScreenAbout();
		ScreenServerBrowser* screenServerBrowser = new ScreenServerBrowser();
		ScreenSettings* screenSettings = new ScreenSettings();

		Screen* currentScreen = screenMainMenu;

		Scene scene = MENU;

		void toggleConsole();

		void refreshPlayers();

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
			if (this->scene == MENU) {
				this->layoutManager->doLayout(this->currentScreen);
			}
		}

		void onMouseMoved(const int x, const int y) const;

		void setScreen(const string& name) {
			Screen* changedScreen;

			if (name == "about") {
				changedScreen = this->screenAbout;
			} else if (name == "main") {
				changedScreen = this->screenMainMenu;
			}

			if (name == "servers") {
				changedScreen = this->screenServerBrowser;
			}

			if (name == "settings") {
				changedScreen = this->screenSettings;
			}

			if (name == "playerSetup") {
				changedScreen = this->screenPlayerSetup;
			}
			
			this->layoutManager->onChanged(changedScreen);
			this->layoutManager->doLayout(changedScreen);
			this->currentScreen = changedScreen;
		}

		std::map<std::chrono::_V2::system_clock::time_point, string> messages;
	private:
		Gui();

		LayoutManager* layoutManager = new LayoutManager();
};

