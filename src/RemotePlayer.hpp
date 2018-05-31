#pragma once

#include "Entity.hpp"

#include <string>

using namespace std;

class RemotePlayer {
	public:
		RemotePlayer();

		int id;
		string username;
		Entity* ent = new Entity();
};
