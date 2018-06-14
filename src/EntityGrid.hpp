#pragma once

#include <algorithm>
#include <vector>

#include "Entity.hpp"

class EntityGrid : public Grid {
	public: 
		EntityGrid() : Grid(GRID_SIZE, GRID_SIZE) {}
		int lastUnregisteredEntityId = -1;

		void add(Entity* e) {
			this->entities[this->lastUnregisteredEntityId--] = e;
		}

		void remove(Entity* e) {
			//this->entities.erase(std::remove(this->entities.begin(), this->entities.end(), e), this->entities.end());
		}

		Entity* get(int id) {
			if (this->entities.find(id) == this->entities.end()) {
				this->entities[id] = new Entity();
			}

			return this->entities[id];
		}

		map<int, Entity*> entities;
};
