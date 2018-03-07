#include "World.hpp"

class GameState {
	public:
		static GameState& get() {
			static GameState instance;

			return instance;
		}

		Entity* getPlayer(int p) {
			return GameState::get().world->entityGrid->entities.at(p);
		}

		void loadWorld(string worldName);
		World* world;

		GameState(GameState const&) = delete;
		void operator=(GameState const&) = delete;

	private:
		GameState() {}
};


