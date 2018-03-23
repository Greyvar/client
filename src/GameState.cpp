#include "GameState.hpp"

void GameState::loadWorld(string worldName) {
	world = new World();

	Entity* bob = new Entity();
	bob->textureName = "playerRed.png";
	bob->pos->x = 32;
	bob->pos->y = 32;
	bob->pos->w = 64;
	bob->pos->h = 64;

	world->addEntity(bob);
}
