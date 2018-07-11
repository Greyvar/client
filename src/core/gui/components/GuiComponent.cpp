#include "GuiComponent.hpp"

GuiComponent::GuiComponent() {

}

void GuiComponent::setConstraints(LayoutConstraints* lc) {
	this->layoutConstraints.x  = lc->x;
	this->layoutConstraints.y = lc->y;
}

