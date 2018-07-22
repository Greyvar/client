#include "Screen.hpp"

using std::move;

void Screen::add(GuiComponent* comp, LayoutConstraints* cons) {
	comp->setConstraints(cons);

	this->components.push_back(move(comp));
}

void Screen::selectNextItem() {
	
}

void Screen::selectPrevItem() {}
void Screen::executeCurrentItem() {}

