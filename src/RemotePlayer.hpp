#pragma once

#include "Entity.hpp"

#include <climits>
#include <string>

using namespace std;

class RemotePlayer {
	public:
		RemotePlayer();

		int id = INT_MIN;
		string username = "unnamed player";
		Entity* ent = new Entity();
};
