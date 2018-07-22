#pragma once

#include "Renderer.hpp"
#include "GuiComponent.hpp"

using std::string;

class Button: public GuiComponent {
	public:
		SDL_Color color{};

		Button(const string& text) : Button(text, {0,0,0, 255}) {
		}

		Button(const string& text, SDL_Color color) {
			this->text = text;
			this->color = color;

			this->rendererFunc = "button";
			this->minimumHeight = 75;
		}

		string getText() const {
			return this->text;
		}

	private:
		string text{};
};
