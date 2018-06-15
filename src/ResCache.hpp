#pragma once

#include <map>
#include <SDL2/SDL.h>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

class ResCache {
	public:
		SDL_Texture* loadTexture(string filename);
		SDL_Texture* loadTexture(string filename, uint32_t primaryColor);
		SDL_Texture* loadEntity(string filename);
		SDL_Texture* loadEntity(string filename, uint32_t primaryColor);
		SDL_Texture* loadHud(string filename);
		SDL_Texture* loadTile(string filename);


		FT_Face* loadFont(string filename, int size);

		void loadStartup();

	private:
		map<string, SDL_Texture*> textureCache = {};

		map<string, FT_Face*> fontCache;
};
