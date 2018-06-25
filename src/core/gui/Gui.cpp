#include <string>

#include "Gui.hpp"
#include "common.hpp"
#include "cvars.hpp"
#include "startup.hpp"

using namespace std;

void Gui::toggleConsole() {
	playSound("interface/interface3.wav", UI);

	if (this->scene == CONSOLE) {
		this->scene = PLAY;
	} else {
		this->scene = CONSOLE;
	}
}
