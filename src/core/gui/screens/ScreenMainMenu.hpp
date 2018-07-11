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

		void setupComponents();

		string getRandomSubtitle();
	private:
		Menu* menu = new Menu();
		string subtitle; 
};
