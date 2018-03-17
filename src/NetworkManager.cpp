#include <iostream>
#include <stdio.h>
#include <SDL2/SDL_net.h>

#include "NetworkManager.hpp"

using namespace std;

void NetworkManager::connectToServer() {
	IPaddress ip;
	TCPsocket socket;
	char buffer[512];

	if (SDLNet_Init() < 0) {
		cout << "SDL Net init failed: " << SDLNet_GetError() << endl;
		return;
	}

	if (SDLNet_ResolveHost(&ip, "localhost", 1337) < 0) {
		cout << "Failed to resolve host: " << SDLNet_GetError() << endl;
		return;
	}

	if (!(socket = SDLNet_TCP_Open(&ip))) {
		cout << "Failed to open socket: " << SDLNet_GetError() << endl;
	}

	int result = SDLNet_TCP_Recv(socket, buffer, sizeof(buffer));

	if (!result) {
		cout << "Failed to recv: " << SDLNet_GetError() << endl;
	} else {
		cout << buffer << endl;
	}

	SDLNet_TCP_Close(socket); SDLNet_Quit();
}
