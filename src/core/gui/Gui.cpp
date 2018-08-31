#include <string>

#include "Gui.hpp"
#include "common.hpp"
#include "cvars.hpp"
#include "startup.hpp"

using namespace std;

Gui::Gui() {
	this->layoutManager->onChanged(this->currentScreen);
}

void Gui::toggleConsole() {
	playSound("interface/interface3.wav", UI);

	if (this->scene == CONSOLE) {
		this->scene = PLAY;
	} else {
		this->scene = CONSOLE;
	}
}

void Gui::refreshPlayers() {
	this->screenPlayerSetup->setupComponents();
	this->layoutManager->onChanged(this->screenPlayerSetup);
	this->layoutManager->doLayout(this->screenPlayerSetup);
}

void Gui::onMouseMoved(const int x, const int y) const {
	if (this->scene == MENU) {
		this->currentScreen->onMouseMoved(x, y);
	}
}
