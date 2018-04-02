#pragma once

#include <vector>

#include "Entity.hpp"

class EntityGrid : public Grid {
	public: 
		EntityGrid() : Grid(10, 8) {}

		void add(Entity* e) {
			this->entities.push_back(e);
		}

		vector<Entity*> entities;
};
