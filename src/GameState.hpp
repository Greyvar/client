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

		static GameState& get() {
			static GameState instance;

			return instance;
		}

		void onPlayerSpawn(RemotePlayer* rp);

		Entity* getPlayer(int p) {
			return GameState::get().world->entityGrid->entities.at(p);
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
		std::vector<RemotePlayer*> remotePlayers;

		GameState() {
			// Initializing the UI here means it is delayed until the first 
			// get() istead of at startup. This allows us more flexibility to 
			// set cvars before startup.

			this->ui = new UserInterface();

			this->localPlayers.push_back(new LocalPlayer());
		}
};


