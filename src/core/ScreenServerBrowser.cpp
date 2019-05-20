#include "ScreenServerBrowser.hpp"
#include "../components/Label.hpp"
#include "../components/Button.hpp"
#include "../components/Menu.hpp"
#include "NetworkManager.hpp"
#include "gui/Gui.hpp"

#include <vector>

class Server {
	public:
		Server(string address, int ping) {
			this->address = address;
			this->ping = ping;
		}

		string address;
		int ping;
};

vector<Server*> servers; 

void ScreenServerBrowser::setupComponents() {
	auto cons = new LayoutConstraints();

	servers.push_back(new Server("localhost", 123));
	servers.push_back(new Server("other server", 456));
	servers.push_back(new Server("asdf", 999));

	auto lbl = new Label("Greyvar >> Servers", 48);
	cons->rowWeight = 0;
	this->add(lbl, cons);

	cons->row++;
	cons->rowWeight = 0;
	this->add(new Label("^3Address"), cons);

	cons->col++;
	this->add(new Label("^3Ping"), cons);

	cons->col++;
	this->add(new Label("^3Details"), cons);


	for (auto server : servers) {
		cons->row++;
		cons->col = 0;
		this->add(new Label(server->address, 24, false, false, false), cons);

		cons->col++;
		this->add(new Label(to_string(server->ping), 24, false, false, false), cons);

		cons->col++;
		this->add(new Label("...", 24, false, false, false), cons);
	}

	cons->row++;
	cons->rowWeight = 1;
	cons->colWeight = 1;
	this->add(new Label("Spacer space space space space"), cons);

	auto btnBack = new Button("Back", []() {
		Gui::get().setScreen("main");
	});

	cons->row++;
	cons->rowWeight = 0;
	cons->col = 0;
	this->add(btnBack, cons);

	auto button = new Button("Connect", []() { 
		Gui::get().setScreen("playerSetup");
	});

	cons->col = 2;
	cons->rowWeight = 0;
	cons->colWeight = 0;
	this->add(button, cons);
}


void ScreenServerBrowser::executeCurrentItem() {
	NetworkManager::get().connectToServer("localhost");
}
