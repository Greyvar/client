#pragma once

#include <SDL2/SDL_net.h>
#include <queue>

#include "LocalPlayer.hpp"
#include "YamlNode.hpp"

const string ETB = "---\n";

class NetworkManager {
	public:
		LocalPlayer* lastLocalPlayerToJoin; 
		
		static NetworkManager& get() {
			static NetworkManager instance;

			return instance;
		}

		NetworkManager(NetworkManager const&) = delete;
		void operator=(NetworkManager const&) = delete;

		void connectToServer(const string& server);

		void sendHelo(LocalPlayer* lp);
		void sendInit();

		void sendMovr(int x, int y, string username);

		bool waitingForMove = false;

		void send(YamlNode* node, string command);

		void recvAll();
		
		void handlePacketQueue();

		void disconnect();

		bool isConnected();

	private:
		NetworkManager() {
			this->set = SDLNet_AllocSocketSet(1);	
		}

		string packetBuf = "";

		TCPsocket socket;
		SDLNet_SocketSet set;

		std::queue<YamlNode*> packetQueue; 

};
