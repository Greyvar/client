#include "Renderer.hpp"
#include "RemotePlayer.hpp"

RemotePlayer::RemotePlayer() {
	this->ent->textureName = "playerBob.png";
	this->ent->pos->x = 32;
	this->ent->pos->y = 32;
	this->ent->pos->w = TILE_SIZE;
	this->ent->pos->h = TILE_SIZE;
}
