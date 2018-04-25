#include "Renderer.hpp"
#include "GameState.hpp"

void GameState::loadWorld(string worldName) {
	world = new World();

}

void GameState::onPlayerSpawn(RemotePlayer* rp) {
	this->remotePlayers.push_back(rp);

	Entity* bob = rp->ent;

	this->world->addEntity(bob);
}
