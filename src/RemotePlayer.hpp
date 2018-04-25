#pragma once

#include "Entity.hpp"

#include <string>

using namespace std;

class RemotePlayer {
	public:
		RemotePlayer();

		string username;
		Entity* ent = new Entity();
};
