#include <iostream>

#include "ScreenMainMenu.hpp"
#include "gui/components/Label.hpp"
#include "startup.hpp"
#include "gui/Gui.hpp"

using namespace std;

string ScreenMainMenu::getRandomSubtitle() {
	cout << "is motd set? " << cvarIsset("motd") << endl;

	if (cvarIsset("motd")) {
		return cvarGet("motd");
	}

	std::vector<string> subtitles;
	subtitles.push_back(move("Hello there!"));
	subtitles.push_back(move("No Java here, buddy."));
	subtitles.push_back(move("I like to code it code it"));
	subtitles.push_back(move("mooorawr"));

	int c = rand() % subtitles.size();

	return subtitles.at(c);
}

void quitMenuAction() {
	quitGame();
}

void aboutMenuAction() {
	Gui::get().setScreen("about");
}

void settingsMenuAction() {
	Gui::get().setScreen("settings");
}

void serversMenuAction() {
	Gui::get().setScreen("servers");
}

void ScreenMainMenu::setupComponents() {
	auto cons = new LayoutConstraints();

	auto lblTitle = new Label("Greyvar");
	lblTitle->fontSize = 48;

	cons->colWeight = 1;
	cons->rowWeight = 0;
	this->add(lblTitle, cons);


	auto lblSubtitle = new Label("^3" + this->getRandomSubtitle());

	cons->row++;
	cons->rowWeight = 0;
	this->add(lblSubtitle, cons);

	this->menu->add("Play", &serversMenuAction);
	this->menu->add("Settings", &settingsMenuAction);
	this->menu->add("About", &aboutMenuAction);
	this->menu->add("Quit", &quitMenuAction);

	cons->row++;
	cons->rowWeight = 1;
	cons->col = 0;
	cons->colWeight = 1;
	this->add(menu, cons);
}

void ScreenMainMenu::selectNextItem() {
	this->menu->selectNextMenuItem();
}

void ScreenMainMenu::selectPrevItem() {
	this->menu->selectPrevMenuItem();
}

void ScreenMainMenu::executeCurrentItem() {
	this->menu->executeCurrentMenuItem();
}
