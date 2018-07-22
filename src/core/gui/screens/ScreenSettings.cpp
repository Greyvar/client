#include "ScreenSettings.hpp"
#include "../components/Label.hpp"

void ScreenSettings::setupComponents() {
	auto cons = new LayoutConstraints();

	auto lbl = new Label("Settings", 48);
	this->add(lbl, cons);

}
