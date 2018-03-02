#ifndef H_TILE
#define H_TILE

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

class Tile {
	public:
		Tile(string texture, bool traversable);

		SDL_Texture *tex; 

		string textureName;

	private:
		bool traversable;

};

#endif
