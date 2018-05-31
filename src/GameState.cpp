#include "Renderer.hpp"
#include "GameState.hpp"

void GameState::clear() {
	for (auto rp : this->remotePlayers) {
		delete(rp.second);
	}

	this->remotePlayers.clear();

	for (auto lp : this->localPlayers) {
		delete(lp);
	}

	this->localPlayers.clear();
}

void GameState::loadWorld(string worldName) {
	this->world = new World();
}

void GameState::onPlayerJoin(RemotePlayer* rp) {
	this->remotePlayers[rp->id] = rp;

	Entity* bob = rp->ent;

	this->world->addEntity(bob);
}
