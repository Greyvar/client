#include <boleas/boleas.hpp>

#include "gui/screens/Screens.hpp"
#include "net/NetClient.hpp"

#include <boleas/gui/Gui.hpp>
#include <boleas/cvars.hpp>

#include <cstdlib>
#include <ctime>
#include <iostream>

using std::cout;
using std::endl;

void hookMainLoop() {
	NetClient::get().sendRecvFrame();

}

void setupNetworkThread() {
	NetClient::get().processServerFrames();
}

int mainGreyvarCore(int argc, char* argv[]) {
	cout << "Greyvar (core) " << endl << "--------------" << endl;

	setupScreens();
	setupNetworkThread();

	boleasHookInput = &hookMainLoop;

	Gui::get().setScreen("main");

	boleasPrintVersion();
	boleasStartEngine(argc, argv);

	cout << "Everything has quit. Bye! " << endl;

	return 0;
}
