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

void GameState::onNewLocalPlayer(LocalPlayer* lp) {
	lp->username = "plr " + to_string(this->localPlayers.size());
	this->localPlayers.push_back(lp);
}

void GameState::onRemoveLocalPlayer(LocalPlayer* lp) {
	this->localPlayers.erase(std::remove(this->localPlayers.begin(), this->localPlayers.end(), lp), this->localPlayers.end());
}
