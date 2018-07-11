#include <SDL2/SDL_image.h>
#include <iostream>

#include "cvars.hpp"
#include "Renderer.hpp"
#include "ResCache.hpp"

using namespace std;

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            return p[0] << 16 | p[1] << 8 | p[2];
        } else {
            return p[0] | p[1] << 8 | p[2] << 16;
		}

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void replaceColors(SDL_Surface* img, uint32_t primaryColor) {
	uint32_t replaceColor = SDL_MapRGB(img->format, 230, 23, 230);

	SDL_LockSurface(img);

	for (int x = 0; x < img->w; x++) {
		for (int y = 0; y < img->h; y++) {
			if (getpixel(img, x, y) == replaceColor) {
				putpixel(img, x, y, primaryColor);
			}
		}
	}

	SDL_UnlockSurface(img);
}

SDL_Texture* ResCache::loadTexture(const string& filename) {
	return this->loadTexture(filename, 0);
}

SDL_Texture* ResCache::loadTexture(const string& filename, uint32_t primaryColor) {
	string textureNameKey = filename + ":" + to_string(primaryColor);

	if (this->textureCache.count(textureNameKey) == 0) {
		SDL_Surface *img = IMG_Load(string(string("res/img/textures/") + filename).c_str());

		if (img == nullptr) {
			std::cout << "error" << SDL_GetError() << std::endl;
		} else {
			if (cvarGetb("debug_textures")) {
				std::cout << "texture loaded: " << filename << std::endl;
			}
		}
	
		if (primaryColor != 0) {
			cout << "Generating replacement color for tex: " << textureNameKey << endl;
			replaceColors(img, primaryColor);
		}

		SDL_Texture *tex = SDL_CreateTextureFromSurface(Renderer::get().sdlRen, img);

		this->textureCache[textureNameKey] = tex;

		SDL_FreeSurface(img);
	}

	return this->textureCache[textureNameKey];
}

SDL_Texture* ResCache::loadEntity(const string& filename) {
	return this->loadEntity(filename, 0);
}

SDL_Texture* ResCache::loadEntity(const string& filename, uint32_t primaryColor) {
	return this->loadTexture(string("entities/" + filename), primaryColor);
}

SDL_Texture* ResCache::loadHud(const string& filename) {
	return this->loadTexture(string("hud/" + filename), 0);
}

SDL_Texture* ResCache::loadTile(const string& filename) {
	return this->loadTexture(string("tiles/" + filename));
}

FT_Face* ResCache::loadFont(const string& filename, int size) {
	std::string tag = filename + ":" + std::to_string(size);

	if (this->fontCache.count(tag) == 0) {
		this->fontCache[tag] = new FT_Face;

		cout << "Loading font " << filename << endl;

		auto loadFontResult = FT_New_Face(*Renderer::get().freetypeLib, string("res/ttf/").append(filename).c_str(), 0, this->fontCache[tag]);

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

