#include "Screen.hpp"

void Screen::add(GuiComponent* comp, LayoutConstraints* cons) {
	comp->setConstraints(cons);

	this->components.push_back(comp);
}
