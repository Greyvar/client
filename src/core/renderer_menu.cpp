#include "GameState.hpp"
#include "Renderer.hpp"
#include "gui/components/Label.hpp"

using namespace std;

void renderComponent(GuiComponent* component) {
	renderTextShadowWithBackground("^1<unsupported component!>", component->pos.x, component->pos.y, 24, {100, 100, 100, 255}, 0);
}

void renderLabel(Label* lbl) {
	renderTextShadowWithBackground(lbl->getText(), lbl->pos.x, lbl->pos.y, lbl->fontSize, {100, 100, 100, 255}, 0);
}


void renderPanel() {
	renderBackgroundSolidColor({130, 130, 130, 255});

	auto currentScreen = GameState::get().gui->currentScreen;

	if (currentScreen != nullptr) {
		for (auto component : currentScreen->components) {
			if (component->rendererFunc == "label") {
				renderLabel((Label*)component);
			} else {
				renderComponent(component);
			}
		}
	}
}

