#include "ScreenServerBrowser.hpp"
#include "../components/Label.hpp"

void ScreenServerBrowser::setupComponents() {
	auto cons = new LayoutConstraints();

	auto lbl = new Label("Servers", 48);
	this->add(lbl, cons);
}
