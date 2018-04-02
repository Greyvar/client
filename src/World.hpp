#pragma once

#include <map>
#include "TileGrid.hpp"
#include "EntityGrid.hpp"

using namespace std;

class World {
	public: 
		TileGrid *tileGrid = new TileGrid();
		EntityGrid *entityGrid = new EntityGrid();

		void addEntity(Entity* e);
};
