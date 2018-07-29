#include "ScreenSettings.hpp"
#include "../components/Label.hpp"
#include "../components/Menu.hpp"
#include "gui/Gui.hpp"

void actionBack() {
	Gui::get().setScreen("main");
}

void ScreenSettings::setupComponents() {
	auto cons = new LayoutConstraints();
	cons->rowWeight = 0;

	auto lbl = new Label("Settings", 48);
	this->add(lbl, cons);

	this->menu = new Menu();
	this->menu->add("Fullscreen");
	this->menu->add("Foo");
	this->menu->add("Bar");
	this->menu->add("Back", actionBack);
	cons->row++;
	cons->rowWeight = 1;
	this->add(this->menu, cons);
}

void ScreenSettings::selectNextItem() {
	this->menu->selectNextMenuItem();
}

void ScreenSettings::selectPrevItem() {
	this->menu->selectPrevMenuItem();
}

void ScreenSettings::executeCurrentItem() {
	this->menu->executeCurrentMenuItem();
}

