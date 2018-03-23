#include <iostream>
#include <stdio.h>
#include <SDL2/SDL_net.h>

#include "YamlNode.hpp"
#include "NetworkManager.hpp"

using namespace std;

void NetworkManager::connectToServer() {
	IPaddress ip;

	if (SDLNet_Init() < 0) {
		cout << "SDL Net init failed: " << SDLNet_GetError() << endl;
		return;
	}

	if (SDLNet_ResolveHost(&ip, "localhost", 1337) < 0) {
		cout << "Failed to resolve host: " << SDLNet_GetError() << endl;
		return;
	}

	if (!(this->socket = SDLNet_TCP_Open(&ip))) {
		cout << "Failed to open socket: " << SDLNet_GetError() << endl;
	}
}

void NetworkManager::recvAll() {
	if (!this->isConnected()) {
		cout << "not connected" << endl;
		return;
	}


	char buffer[512];
	int result = SDLNet_TCP_Recv(this->socket, buffer, sizeof(buffer));

	if (!result) {
		cout << "Failed to recv: " << SDLNet_GetError() << endl;
	} else {
		cout << "recv: " << buffer << endl;
	}
}

void NetworkManager::sendHelo() {
	YamlNode* helo = new YamlNode();

	helo->attr("username", "test");

	this->send(helo, "HELO");

	delete helo;
}

void NetworkManager::send(YamlNode* node, string command) {
	node->attr("command", command);

	std::string message = node->toString();
	message.push_back(ETB);

	SDLNet_TCP_Send(this->socket, message.c_str(), sizeof(message));
}

void NetworkManager::disconnect() {
	SDLNet_TCP_Close(this->socket); SDLNet_Quit();
}

bool NetworkManager::isConnected() {
	return SDLNet_SocketReady(this->socket);
}
