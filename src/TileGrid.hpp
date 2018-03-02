#ifndef H_TILEGRID
#define H_TILEGRID

#include <map>

#include "Grid.hpp"
#include "Tile.hpp"

class TileGrid : public Grid {
	public:
		TileGrid() : Grid(10, 8) {
			for (int col = 0; col < this->w; col++) {
				for (int row = 0; row < this->h; row++) {
					this->tiles[row][col] = new Tile(string("construct.png"), false);
				}
			}
		}

		Tile* get(int row, int col) {
			return this->tiles[row][col];
		}

	private:
		map<int, map<int, Tile*>> tiles;
};

#endif
