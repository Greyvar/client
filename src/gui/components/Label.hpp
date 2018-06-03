#include <string>

#include "GuiComponent.hpp"

using namespace std;

class Label: public GuiComponent {
	public:
		public Label(string text) {
			this->text = text;
		}

	private: 
		string text;
}
