#include <string>

#include "GuiComponent.hpp"

using namespace std;

class Label: public GuiComponent {
	public:
		Label(const string& text) : Label(text, 24) {}

		Label(const string& text, int fontSize) {
			this->rendererFunc = "label";
			this->text = text;

			this->minimumHeight = this->fontSize * 1.9;
			this->minimumWidth = this->text.size() * 18;
			this->fontSize = fontSize;
		}

		string getText() {
			return this->text;
		}

		int fontSize = 24;

	private: 
		string text;
};
