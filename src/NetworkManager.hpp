#ifndef H_NETWORK_MANAGER
#define H_NETWORK_MANAGER

class NetworkManager {
	public:
		static NetworkManager& get() {
			static NetworkManager instance;

			return instance;
		}

		NetworkManager(NetworkManager const&) = delete;
		void operator=(NetworkManager const&) = delete;

		void connectToServer();

	private:
		NetworkManager() {}
};

#endif
