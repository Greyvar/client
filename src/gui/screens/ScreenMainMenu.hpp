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

		std::string getRandomSubtitle() {
			cout << "is motd set? " << cvarIsset("motd") << endl;

			if (cvarIsset("motd")) {
				return cvarGet("motd");
			}

			std::vector<string> subtitles;
			subtitles.push_back("Hello there!");
			subtitles.push_back("No Java here, buddy.");
			subtitles.push_back("I like to code it code it");
			subtitles.push_back("mooorawr");

			int c = rand() % subtitles.size();

			return subtitles.at(c);
		}


	private:
		Menu* menu = new Menu();
		string subtitle; 
};
