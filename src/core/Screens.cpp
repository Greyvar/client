#include "ScreenMainMenu.hpp"
#include "ScreenSettings.hpp"
#include "ScreenSplash.hpp"
#include "ScreenAbout.hpp"

#include <boleas/boleas.hpp>
#include <boleas/gui/Gui.hpp>

void setupScreens() {
	Gui::get().addScreen("main", new ScreenMainMenu());
	Gui::get().addScreen("settings", new ScreenSettings());
	Gui::get().addScreen("splash", new ScreenSplash());
	Gui::get().addScreen("about", new ScreenAbout());
}
