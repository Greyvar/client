#include "ScreenMainMenu.hpp"

std::string ScreenMainMenu::getRandomSubtitle() {
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
