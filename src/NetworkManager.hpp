#ifndef H_NETWORK_MANAGER
#define H_NETWORK_MANAGER

#include <SDL2/SDL_net.h>

#include "YamlNode.hpp"

#define ETB '\x17'

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
		NetworkManager() {}

		TCPsocket socket;
};

#endif
