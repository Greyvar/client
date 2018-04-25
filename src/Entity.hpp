#pragma once

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class Entity {
	public:
		string textureName;

		SDL_Rect* pos = new SDL_Rect;
};

