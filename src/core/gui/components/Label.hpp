#include <string>

#include "GuiComponent.hpp"

using namespace std;

class Label: public GuiComponent {
	public:
		Label(string text) {
			this->rendererFunc = "label";
			this->text = text;
		}

		string getText() {
			return this->text;
		}

		int fontSize = 24;

	private: 
		string text;
};
