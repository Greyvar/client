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

FT_Face* ResCache::loadFont(string filename) {
	filename = "res/ttf/" + filename;

	if (this->fontCache.count(filename) == 0) {
		this->fontCache[filename] = new FT_Face;

		cout << "Loading font " << filename << endl;

		auto loadFontResult = FT_New_Face(*Renderer::get().freetypeLib, filename.c_str(), 0, this->fontCache[filename]);

		cout << "Load font result: " << loadFontResult << endl;

		FT_Set_Pixel_Sizes(*this->fontCache[filename], 0, 48);

		if (this->fontCache[filename] == nullptr) {
			cout << "Failed to load font: " << filename << endl;
		} else {
			cout << "Cached font: " << filename << endl;
		}
	}

	cout << "Loading from cache: " << filename << endl;

	return this->fontCache[filename];
}

void ResCache::loadStartup() {
//	this->loadFont("DejaVuSans.ttf");
}

