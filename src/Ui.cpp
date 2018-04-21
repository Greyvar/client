#include <string>

#include "Ui.hpp"
#include "common.hpp"
#include "cvars.hpp"

using namespace std;

std::string getRandomSubtitle() {
	cout << cvarIsset("motd") << endl;

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

void UserInterface::setupMainMenu() {
	this->subtitle = getRandomSubtitle();

	this->mainMenu.push_back(new MenuItem("Play", &startGame));
	this->mainMenu.push_back(new MenuItem("Settings", &quitGame));
	this->mainMenu.push_back(new MenuItem("Quit", &quitGame));

	this->currentMenu = &(this->mainMenu);	
}

void UserInterface::toggleConsole() {
	playSound("interface/interface3.wav", UI);

	if (this->scene == CONSOLE) {
		this->scene = PLAY;
	} else {
		this->scene = CONSOLE;
	}
}
