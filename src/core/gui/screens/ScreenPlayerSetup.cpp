#include "ScreenPlayerSetup.hpp"

#include "GameState.hpp"

#include "../components/Label.hpp"
#include "../components/Button.hpp"
#include "../components/TextureViewer.hpp"
#include "gui/Gui.hpp"

void actionPlay() {

}

void actionPlayerSetupBack() {
	Gui::get().setScreen("servers");
}

void ScreenPlayerSetup::setupComponents() {
	auto cons = new LayoutConstraints();

	this->components.clear();

	this->add(new Label("Greyvar >> Player Setup", 48), cons);

	auto localPlayers = GameState::get().getLocalPlayers();

	for (uint32_t i = 0; i < localPlayers.size(); i++) {
		cons->row = 1;
		cons->rowWeight = 0;
		this->add(new Label("Username: " + localPlayers.at(i)->username), cons);

		cons->row++;
		this->add(new TextureViewer("entities/playerBob.png", 128), cons);

		string inputDeviceIcon = "hud/question.png";

		switch (localPlayers.at(i)->inputDevice.type) {
			case KEYBOARD_AND_POINTER:
				inputDeviceIcon = "hud/keyboard.png";
				break;

			case GAMEPAD:
				inputDeviceIcon = "hud/gamepad.png";
				break;
		}

		cons->row++;
		cons->rowWeight = 1;
		this->add(new TextureViewer(inputDeviceIcon), cons);

		cons->row++;
		cons->rowWeight = 0;
		this->add(new Button("Play", &actionPlay), cons);

		cons->col++;
	}

	cons->row++;
	cons->col = 0;
	this->add(new Button("Back", &actionPlayerSetupBack), cons);
}
