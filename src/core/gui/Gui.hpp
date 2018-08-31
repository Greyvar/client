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
#include "screens/ScreenSplash.hpp"

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

		ScreenDashboard* screenDashboard = new ScreenDashboard();
		ScreenMainMenu* screenMainMenu = new ScreenMainMenu();
		ScreenConsole* screenConsole = new ScreenConsole();
		ScreenPlayerSetup* screenPlayerSetup = new ScreenPlayerSetup();
		ScreenAbout* screenAbout = new ScreenAbout();
		ScreenServerBrowser* screenServerBrowser = new ScreenServerBrowser();
		ScreenSettings* screenSettings = new ScreenSettings();
		ScreenSplash* screenSplash = new ScreenSplash();

		Screen* currentScreen = screenSplash;

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

		void goBack() {
			this->setScreen(this->currentScreen->getPreviousScreenName());
		}

		void setScreen(const string& name) {
			cout << "Changing screen to " << name << endl;

			Screen* changedScreen = nullptr;

			if (name == "about") {
				changedScreen = this->screenAbout;
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

			if (name == "dashboard") {
				changedScreen = this->screenDashboard;
			}

			if (name == "splash") {
				changedScreen = this->screenSplash;
			}

			if (changedScreen == nullptr) {
				// The Chris Houlihan screen. :) 
				changedScreen = this->screenMainMenu;
			}
			
			this->layoutManager->onChanged(changedScreen);
			this->layoutManager->doLayout(changedScreen);
			this->currentScreen = changedScreen;
		}

		std::map<std::chrono::_V2::system_clock::time_point, string> messages;
		
		LayoutManager* layoutManager = new LayoutManager();
	private:
		Gui();

};

