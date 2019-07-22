#include <boleas/boleas.hpp>

#include "Screens.hpp"
#include "net/NetClient.hpp"

#include <boleas/gui/Gui.hpp>
#include <boleas/cvars.hpp>

#include <cstdlib>
#include <ctime>
#include <iostream>

using std::cout;
using std::endl;

int mainGreyvarCore(int argc, char* argv[]) {
	cout << "Greyvar (core) " << endl << "--------------" << endl;

	setupScreens();

	Gui::get().setScreen("main");

	boleasSayHello();
	boleasStartEngine();

	cout << "Everything has quit. Bye! " << endl;

	return 0;
}
