#ifndef TEXTURE_CACHE
#define TEXTURE_CACHE

#include <map>
#include <SDL2/SDL.h>

using namespace std;

class TextureCache {
	public:
		SDL_Texture* load(string filename);
		SDL_Texture* loadEntity(string filename);
		SDL_Texture* loadTile(string filename);
	
	private:
		map<string, SDL_Texture*> cache;
};

#endif
