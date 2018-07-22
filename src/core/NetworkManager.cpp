#include "gui/Gui.hpp"
#include "YamlNode.hpp"
#include "NetworkManager.hpp"
#include "GameState.hpp"
#include "cvars.hpp"

#include "platforms/platform.hpp"

#include <iostream>
#include <cstdio>
#include <SDL2/SDL_net.h>

void NetworkManager::connectToServer(const string& server) {
	IPaddress ip{};

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

	if (this->isConnected()) {
		SDLNet_TCP_Send(this->socket, ETB.c_str(), ETB.size());

		this->sendInit();
	}
}

void handleWelc(YamlNode* welc) {
	cout << "Server version is: " << welc->attr("serverVersion") << endl;
	Gui::get().scene = PLAY;
	Gui::get().addMessage("Connected to " + welc->attr("name"));
}

void handleTile(YamlNode* ytile) {
	Tile* tile = GameState::get().world->tileGrid->get(ytile->attri("col"), ytile->attri("row"));

	if (tile == nullptr) {
		cout << "could not find tile!" << ytile->toString() << endl;
		return; 
	}

	tile->textureName = ytile->attr("tex");
	tile->texHFlip = ytile->attrb("hor");
	tile->texVFlip = ytile->attrb("vrt");
	tile->texRot = ytile->attri("rot");
}

void handleMove(YamlNode* ypacket) {
	NetworkManager::get().waitingForMove = false;

	auto ent = GameState::get().getRemotePlayerById(ypacket->attri("playerId"))->ent;

	ent->pos->x = ypacket->attri("posX");
	ent->pos->y = ypacket->attri("posY");
	
	cout << "player pos: " << ent->pos->x << ":" << ent->pos->y << endl;
}

void handlePlayerQuit(YamlNode* ypacket) {
	GameState::get().removePlayerById(ypacket->attri("id")); 
}

void handlePlayerAlreadyHere(YamlNode* ypacket) {
	auto rp = new RemotePlayer();
	rp->id = ypacket->attri("id");
	rp->username = ypacket->attr("username");
	rp->ent->primaryColor = __builtin_bswap32(ypacket->attri("color"));

	GameState::get().onPlayerJoin(rp);
}

void handlePlrj(YamlNode* plrj) {
	Gui::get().addMessage(plrj->attr("username") + " joined the server");

	handlePlayerAlreadyHere(plrj);
}

void handlePlayerYou(YamlNode* ypacket) {
	auto rp = GameState::get().getRemotePlayerById(ypacket->attri("id"));

	NetworkManager::get().lastLocalPlayerToJoin->remote = rp;
	NetworkManager::get().lastLocalPlayerToJoin = nullptr;
}

void handleEnt(YamlNode* ypacket) {
	auto ent = GameState::get().world->entityGrid->get(ypacket->attri("id"));

	ent->pos->w = 16 * 4;
	ent->pos->h = 16 * 4;
	ent->pos->x = ypacket->attri("x") * 16;
	ent->pos->y = ypacket->attri("y") * 16;

	ent->textureName = ypacket->attr("tex");
}

void handlePacket(YamlNode* ypacket) {
	string command = ypacket->attr("command");

	if (command == "WELC") {
		handleWelc(ypacket);
	} else if (command == "PLRU") { 
		handlePlayerYou(ypacket);
	} else if (command == "PLRJ") { 
		handlePlrj(ypacket);
	} else if (command == "TILE") {
		handleTile(ypacket);
	} else if (command == "MOVE") {
		handleMove(ypacket);
	} else if (command == "BLKD") {
		NetworkManager::get().waitingForMove = false;
	} else if (command == "PLRQ") {
		handlePlayerQuit(ypacket);
	} else if (command == "PLRH") {
		handlePlayerAlreadyHere(ypacket);
	} else if (command == "ENT") {
		handleEnt(ypacket);
	} else if (command == "SPWN") {
		auto rp = GameState::get().getRemotePlayerById(ypacket->attri("id"));

		rp->ent->pos->x = ypacket->attri("posX");
		rp->ent->pos->y = ypacket->attri("posY");
	} else {
		cout << "Unhandled server command: " << command << endl;
	}
}

void NetworkManager::handlePacketQueue() {
	while (!this->packetQueue.empty()) {
		auto packet = this->packetQueue.front();

		if (cvarGetb("debug_recv_packets")) {
			cout << "recv " << packet->toString() << endl;
		}

		handlePacket(packet);

		this->packetQueue.pop();

		delete(packet);
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
			this->packetBuf.append(recvBuffer, sizeof(recvBuffer));

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

void NetworkManager::sendInit() {
	YamlNode* init = new YamlNode();

	this->send(init, "INIT");
}

void NetworkManager::sendHelo(LocalPlayer* lp) {
	this->lastLocalPlayerToJoin = lp;

	YamlNode* helo = new YamlNode();

	helo->attr("username", lp->username);

	this->send(helo, "HELO");
}

void NetworkManager::send(YamlNode* node, string command) {
	node->attr("command", command);

	std::string message = node->toString();
	message += ETB;

	SDLNet_TCP_Send(this->socket, message.c_str(), message.size());

	delete(node);
}

void NetworkManager::sendMovr(int x, int y, string username) {
	YamlNode* movr = new YamlNode();
	movr->attr("username", username);
	movr->attr("x", x);
	movr->attr("y", y);

	this->waitingForMove = true;
	this->send(movr, "MOVR");
}

void NetworkManager::disconnect() {
	SDLNet_TCP_Close(this->socket); SDLNet_Quit();
}

bool NetworkManager::isConnected() {
	SDLNet_CheckSockets(this->set, 10);

	return SDLNet_SocketReady(this->socket);
}
