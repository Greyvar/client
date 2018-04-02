#pragma once

#include <SDL2/SDL_net.h>

#include "YamlNode.hpp"

#define ETB "---\n"

class NetworkManager {
	public:
		static NetworkManager& get() {
			static NetworkManager instance;

			return instance;
		}

		NetworkManager(NetworkManager const&) = delete;
		void operator=(NetworkManager const&) = delete;

		void connectToServer();

		void sendHelo();

		void send(YamlNode* node, string command);

		void recvAll();

		void disconnect();

		bool isConnected();

	private:
		NetworkManager() {
			this->set = SDLNet_AllocSocketSet(1);	
		}

		string packetBuf;

		TCPsocket socket;
		SDLNet_SocketSet set;
};
