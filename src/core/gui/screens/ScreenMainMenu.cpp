#include <iostream>

#include "ScreenMainMenu.hpp"
#include "gui/components/Label.hpp"

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

void ScreenMainMenu::setupComponents() {
	auto cons = new LayoutConstraints();

	auto lblTitle = new Label("Greyvar");
	lblTitle->fontSize = 48;

	cons->weightX = 1;
	cons->weightY = 0;
	this->add(lblTitle, cons);


	auto lblSubtitle = new Label("^3" + this->getRandomSubtitle());

	cons->y++;
	cons->weightY = 1;
	this->add(lblSubtitle, cons);

	cons->x++;
	this->add(new Label("foo"), cons);

	this->menu->add("Play");
	this->menu->add("Settings");
	this->menu->add("About");
	this->menu->add("Quit");

	cons->y++;
	cons->x = 0;
	cons->weightY = 1;
	this->add(menu, cons);
}
