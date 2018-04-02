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

	SDLNet_TCP_AddSocket(this->set, this->socket);

	SDLNet_TCP_Send(this->socket, ETB, sizeof(ETB));
}

void handlePacket(string packet) {
	cout << ">>>" << endl;
	cout << packet << endl;
	cout << ">>>" << endl;
}

void NetworkManager::recvAll() {
	if (!this->isConnected()) {
		cout << "not connected" << endl;
		return;
	}

	char recvBuffer[1024];
	int result = SDLNet_TCP_Recv(this->socket, recvBuffer, sizeof(recvBuffer));

	if (!result) {
		cout << "Failed to recv: " << SDLNet_GetError() << endl;
	} else {
		cout << "recv: " << recvBuffer << endl;

		this->packetBuf.append(recvBuffer);
		memset(&recvBuffer, 0, sizeof(recvBuffer));

		while (true) {
			uint32_t dividerPos = this->packetBuf.find(ETB);

			if (dividerPos == string::npos) {
				break; 
			} else {
				string packet = this->packetBuf.substr(0, dividerPos);
			
				this->packetBuf = this->packetBuf.substr(dividerPos + 4);

				handlePacket(packet);
			}
		}
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
	message += ETB;

	SDLNet_TCP_Send(this->socket, message.c_str(), message.size());
}

void NetworkManager::disconnect() {
	SDLNet_TCP_Close(this->socket); SDLNet_Quit();
}

bool NetworkManager::isConnected() {
	SDLNet_CheckSockets(this->set, 10);

	return SDLNet_SocketReady(this->socket);
}
