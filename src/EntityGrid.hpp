#pragma once

#include <algorithm>
#include <vector>

#include "Entity.hpp"

class EntityGrid : public Grid {
	public: 
		EntityGrid() : Grid(GRID_SIZE, GRID_SIZE) {}

		void add(Entity* e) {
			this->entities.push_back(e);
		}

		void remove(Entity* e) {
			this->entities.erase(std::remove(this->entities.begin(), this->entities.end(), e), this->entities.end());
		}

		vector<Entity*> entities;
};
