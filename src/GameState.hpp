#include "World.hpp"

class GameState {
	public:
		static GameState& get() {
			static GameState instance;

			return instance;
		}

		void loadWorld(string worldName);
		World* world;

		GameState(GameState const&) = delete;
		void operator=(GameState const&) = delete;

	private:
		GameState() {}
};


