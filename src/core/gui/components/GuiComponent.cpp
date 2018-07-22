#include "GuiComponent.hpp"

GuiComponent::GuiComponent() {

}

void GuiComponent::setConstraints(LayoutConstraints* lc) {
	this->layoutConstraints.row  = lc->row;
	this->layoutConstraints.col = lc->col;
	this->layoutConstraints.rowWeight = lc->rowWeight;
	this->layoutConstraints.colWeight = lc->colWeight;
}

