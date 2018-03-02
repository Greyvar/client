#include <SDL2/SDL_image.h>
#include <iostream>

#include "Renderer.hpp"
#include "TextureCache.hpp"

using namespace std;

SDL_Texture* TextureCache::load(string filename) {
	if (this->cache.count(filename) == 0) {
		SDL_Surface *img = IMG_Load(string(string("res/images/textures/") + filename).c_str());

		if (img == nullptr) {
			std::cout << "error" << SDL_GetError() << std::endl;
		} else {
			std::cout << "texture loaded" << std::endl;
		}

		SDL_Texture *tex = SDL_CreateTextureFromSurface(Renderer::get().sdlRen, img);

		this->cache[filename] = tex;

		SDL_FreeSurface(img);
	}

	return this->cache[filename];
}


SDL_Texture* TextureCache::loadEntity(string filename) {
	return this->load(string("entities/" + filename));
}

SDL_Texture* TextureCache::loadTile(string filename) {
	return this->load(string("tiles/" + filename));
}
