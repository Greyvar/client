#include "Renderer.hpp"
#include "GameState.hpp"

void GameState::loadWorld(string worldName) {
	world = new World();

	Entity* bob = new Entity();
	bob->textureName = "playerRed.png";
	bob->pos->x = 32;
	bob->pos->y = 32;
	bob->pos->w = TILE_SIZE;
	bob->pos->h = TILE_SIZE;

	world->addEntity(bob);
}
