#include <iostream>
#include <stdio.h>
#include <SDL2/SDL_net.h>

#include "YamlNode.hpp"
#include "NetworkManager.hpp"
#include "GameState.hpp"
#include "cvars.hpp"

using namespace std;

void NetworkManager::connectToServer(string server) {
	IPaddress ip;

	if (SDLNet_Init() < 0) {
		cout << "SDL Net init failed: " << SDLNet_GetError() << endl;
		return;
	}

	if (SDLNet_ResolveHost(&ip, server.c_str(), 1337) < 0) {
		cout << "Failed to resolve host: " << SDLNet_GetError() << endl;
		return;
	}

	if (!(this->socket = SDLNet_TCP_Open(&ip))) {
		cout << "Failed to open socket: " << SDLNet_GetError() << endl;
	}

	SDLNet_TCP_AddSocket(this->set, this->socket);

	SDLNet_TCP_Send(this->socket, ETB.c_str(), ETB.size());

	this->sendHelo();
}

void handleWelc(YamlNode* welc) {
	cout << "Server version is: " << welc->attr("serverVersion") << endl;
	GameState::get().ui->scene = PLAY;
	GameState::get().ui->addMessage("Connected to " + welc->attr("name"));
}

void handlePlrj(YamlNode* plrj) {
	GameState::get().ui->addMessage("^1" + plrj->attr("nickname") + " ^7joined the server");
}

void handleTile(YamlNode* ytile) {
	Tile* tile = GameState::get().world->tileGrid->get(ytile->attri("col"), ytile->attri("row"));

	if (tile == nullptr) {
		cout << "could not find tile!" << ytile->toString() << endl;
	}

	tile->textureName = ytile->attr("tex");
	tile->texHFlip = ytile->attrb("hor");
	tile->texVFlip = ytile->attrb("vrt");
	tile->texRot = ytile->attri("rot");
}

void handlePacket(YamlNode* ypacket) {
	string command = ypacket->attr("command");

	if (command == "WELC") {
		handleWelc(ypacket);
	} else if (command == "PLRJ") { 
		handlePlrj(ypacket);
	} else if (command == "TILE") {
		handleTile(ypacket);
	} else {
		cout << "Unhandled server command: " << command << endl;
	}
}

void NetworkManager::handlePacketQueue() {
	while (!this->packetQueue.empty()) {
		auto packet = this->packetQueue.front();

		handlePacket(packet);

		this->packetQueue.pop();
	}
}

void NetworkManager::recvAll() {
	while (this->isConnected()) {
		char recvBuffer[512];
		memset(&recvBuffer, 0, sizeof(recvBuffer));

		int result = SDLNet_TCP_Recv(this->socket, recvBuffer, sizeof(recvBuffer));

		if (result <= 0) {
			cout << "Failed to recv: " << SDLNet_GetError() << endl;
			return;
		} else {
			this->packetBuf.append(recvBuffer);

			while (true) {
				string::size_type dividerPos = this->packetBuf.find(ETB);

				if (dividerPos == string::npos) {
					break; // no more ETBs found in packet buffer, break until we have a complete packet
				} else {
					string packet = this->packetBuf.substr(0, dividerPos);
					string afterPacket = this->packetBuf.substr(dividerPos + (ETB.size() - 0));

					this->packetBuf = afterPacket;

					YamlNode* ypacket = YamlNode::fromStringstream(stringstream(packet));

					this->packetQueue.push(ypacket);
				}
			}

		}
	}
}

void NetworkManager::sendHelo() {
	YamlNode* helo = new YamlNode();

	helo->attr("username", cvarGet("username"));

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
