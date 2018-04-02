#pragma once

#include "World.hpp"
#include "Ui.hpp"

class GameState {
	public:
		GameState(GameState const&) = delete;
		void operator=(GameState const&) = delete;

		static GameState& get() {
			static GameState instance;

			return instance;
		}

		Entity* getPlayer(int p) {
			return GameState::get().world->entityGrid->entities.at(p);
		}

		void loadWorld(string worldName);
		World* world;

		std::string serverName = "the construct";

		UserInterface* ui = new UserInterface();

	private:
		GameState() {}
};


