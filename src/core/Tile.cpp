#include "Tile.hpp"

Tile::Tile(const string& textureName, bool traversable) {
	this->tex = nullptr;
	this->textureName = textureName;
	this->traversable = traversable;
}
