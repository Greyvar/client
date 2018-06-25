#include <iostream>

#include "../components/Menu.hpp"

#include "cvars.hpp"
#include "Screen.hpp"

using namespace std;

class ScreenMainMenu: public Screen {
	public: 
		ScreenMainMenu() {
			setupComponents();
		}

		void setupComponents() {
			this->subtitle = this->getRandomSubtitle();

			this->menu->add("Play");
			this->menu->add("Settings");
			this->menu->add("About");
			this->menu->add("Quit");
		}

		string getRandomSubtitle();
	private:
		Menu* menu = new Menu();
		string subtitle; 
};
