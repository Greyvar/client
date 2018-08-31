#pragma once

#include "../components/Menu.hpp"

#include "cvars.hpp"
#include "Screen.hpp"

#include <iostream>

using namespace std;

class ScreenMainMenu: public Screen {
	public: 
		ScreenMainMenu() {
			setupComponents();
		}

		void setupComponents();

		string getRandomSubtitle();
		
	private:
		string subtitle; 
};
