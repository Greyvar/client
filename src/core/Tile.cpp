#include "Tile.hpp"

Tile::Tile(string textureName, bool traversable) {
	this->tex = nullptr;
	this->textureName = textureName;
	this->traversable = traversable;
}
