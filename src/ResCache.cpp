#include <SDL2/SDL_image.h>
#include <iostream>

#include "Renderer.hpp"
#include "ResCache.hpp"

using namespace std;

SDL_Texture* ResCache::loadTexture(string filename) {
	if (this->textureCache.count(filename) == 0) {
		SDL_Surface *img = IMG_Load(string(string("res/img/textures/") + filename).c_str());

		if (img == nullptr) {
			std::cout << "error" << SDL_GetError() << std::endl;
		} else {
			std::cout << "texture loaded: " << filename << std::endl;
		}

		SDL_Texture *tex = SDL_CreateTextureFromSurface(Renderer::get().sdlRen, img);

		this->textureCache[filename] = tex;

		SDL_FreeSurface(img);
	}

	return this->textureCache[filename];
}

SDL_Texture* ResCache::loadEntity(string filename) {
	return this->loadTexture(string("entities/" + filename));
}

SDL_Texture* ResCache::loadTile(string filename) {
	return this->loadTexture(string("tiles/" + filename));
}

FT_Face* ResCache::loadFont(string filename, int size) {
	filename = "res/ttf/" + filename;
	std::string tag = filename + ":" + std::to_string(size);

	if (this->fontCache.count(tag) == 0) {
		this->fontCache[tag] = new FT_Face;

		cout << "Loading font " << filename << endl;

		auto loadFontResult = FT_New_Face(*Renderer::get().freetypeLib, filename.c_str(), 0, this->fontCache[tag]);

		cout << "Load font result: " << loadFontResult << endl;

		FT_Set_Pixel_Sizes(*this->fontCache[tag], 0, size);

		if (this->fontCache[tag] == nullptr) {
			cout << "Failed to load font: " << filename << endl;
		} else {
			cout << "Cached font: " << filename << endl;
		}
	}

	return this->fontCache[tag];
}

void ResCache::loadStartup() {
//	this->loadFont("DejaVuSans.ttf");
}

