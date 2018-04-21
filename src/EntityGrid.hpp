#pragma once

#include <vector>

#include "Entity.hpp"

class EntityGrid : public Grid {
	public: 
		EntityGrid() : Grid(GRID_SIZE, GRID_SIZE) {}

		void add(Entity* e) {
			this->entities.push_back(e);
		}

		vector<Entity*> entities;
};
