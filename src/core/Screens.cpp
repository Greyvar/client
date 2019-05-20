#include "ScreenMainMenu.hpp"

#include <boleas.hpp>

void setupScreens() {
	boleasAddScreen("main", new ScreenMainMenu());
}
