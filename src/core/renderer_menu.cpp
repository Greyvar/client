#include "GameState.hpp"
#include "Renderer.hpp"
#include "gui/components/Label.hpp"
#include "gui/components/TextureViewer.hpp"
#include "gui/components/Button.hpp"
#include "gui/components/Menu.hpp"
#include "gui/Gui.hpp"
#include "gui/utils/TextAlignment.hpp"

using namespace std;

void renderComponent(GuiComponent* component) {
	renderTextShadowWithBackground("^1<unsupported component!>", component->pos.x, component->pos.y, 24, {100, 100, 100, 255}, 0);
}

void renderLabel(Label* lbl) {
	renderTextShadowWithBackground(lbl->getText(), lbl->pos.x, lbl->pos.y, lbl->fontSize, {100, 100, 100, 255}, 0);
}

void renderButton(Button* btn) {
	renderRect(btn->color, btn->pos.x, btn->pos.y, btn->pos.w, btn->pos.h);

	SDL_Color shadow  = btn->color;
	shadow.r -= 100;

	renderRect(shadow, btn->pos.x + 5, btn->pos.y + 5, btn->pos.w - 10, btn->pos.h - 10);

	renderTextShadowWithBackground(btn->getText(), btn->pos.x + 16, btn->pos.y + 42, 32, btn->color, 0);
}

void renderMenu(Menu* menu) {
	const int itemHeight = 30;
	int yOffset = 32;

	const int selectedIndex = menu->getSelectedIndex();

	for (int i = 0; i < menu->getItemCount(); i++) {
		SDL_Color color{255, 255, 255, 255};

		if (i == selectedIndex) {
			color = {0, 255, 255, 255};
			renderTextShadow(string(">"), menu->pos.x - 20, menu->pos.y + yOffset + (i * itemHeight), LEFT, 24, color);
		}

		renderTextShadow(menu->getItemName(i), menu->pos.x, menu->pos.y + yOffset + (i * itemHeight), LEFT, 24, color);
	}
}

void renderTexture(TextureViewer* view) {
	SDL_Rect pos{};
	pos.x = view->pos.x;
	pos.y = view->pos.y;
	pos.w = view->size;
	pos.h = view->size;

	auto tex = Renderer::get().resCache->loadTexture(view->textureName);

	SDL_RenderCopy(Renderer::get().sdlRen, tex, nullptr, &pos);
}

void renderPanel() {
	renderBackgroundSolidColor({130, 130, 130, 255});

	auto currentScreen = Gui::get().currentScreen;

	if (currentScreen != nullptr) {
		for (auto component : currentScreen->components) {
			if (component->rendererFunc == "label") {
				renderLabel((Label*)component);
			} else if (component->rendererFunc == "button") {
				renderButton((Button*)component);
			} else if (component->rendererFunc == "menu") {
				renderMenu((Menu*)component);
			} else if (component->rendererFunc == "texture") {
				renderTexture((TextureViewer*)component);
			} else {
				renderComponent(component);
			}
		}
	}
}

