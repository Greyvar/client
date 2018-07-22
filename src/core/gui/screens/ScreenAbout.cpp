#include "ScreenAbout.hpp"
#include "../components/Label.hpp"
#include "../components/Menu.hpp"
#include "../components/MenuItem.hpp"
#include "gui/Gui.hpp"

void ScreenAbout::setupComponents() {
	auto cons = new LayoutConstraints();
	cons->colWeight = 1;
	cons->rowWeight = 0;

	auto lbl = new Label("About Greyvar");
	lbl->fontSize = 48;
	this->add(lbl, cons);

	auto lblDev = new Label("Greyvar is developed entirely by James Read. Yay.");
	cons->row++;
	cons->rowWeight = 1;
	this->add(lblDev, cons);

	auto mnu = new Menu();

	mnu->add("Return");

	cons->row++;
	cons->rowWeight = 0;
	this->add(mnu, cons);
}

void ScreenAbout::executeCurrentItem() {
	Gui::get().setScreen("main");
}
