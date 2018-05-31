#pragma once

#include <vector>

#include "World.hpp"
#include "Ui.hpp"
#include "LocalPlayer.hpp"
#include "RemotePlayer.hpp"

class GameState {
	public:
		GameState(GameState const&) = delete;
		void operator=(GameState const&) = delete;

		void clear();

		static GameState& get() {
			static GameState instance;

			return instance;
		}

		void onPlayerJoin(RemotePlayer* rp);


		RemotePlayer* getRemotePlayerById(int p) {
			return GameState::get().remotePlayers[p];
		}

		LocalPlayer* getFirstLocalPlayer() {
			return this->localPlayers.at(0);
		}

		void loadWorld(string worldName);
		World* world;

		std::string serverName = "the construct";

		UserInterface* ui;
	private:
		std::vector<LocalPlayer*> localPlayers;
		std::map<int, RemotePlayer*> remotePlayers;

		GameState() {
			// Initializing the UI here means it is delayed until the first 
			// get() istead of at startup. This allows us more flexibility to 
			// set cvars before startup.

			this->ui = new UserInterface();

			auto lp = new LocalPlayer();
			lp->inputDevice.type = KEYBOARD;
			lp->inputDevice.device.keyboard = 1;

			this->localPlayers.push_back(lp);
		}
};


