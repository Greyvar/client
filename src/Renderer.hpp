#ifndef RENDERER
#define RENDERER

#include <SDL2/SDL.h>
#include "TextureCache.hpp"
#include "World.hpp"

class Renderer {	
	public: 
		static Renderer& get() {
			static Renderer instance;

			return instance;
		}

		static void set(SDL_Renderer* renderer) {
			get().sdlRen = renderer;
		}

		TextureCache* textureCache = new TextureCache();
		SDL_Renderer* sdlRen;

		Renderer(Renderer const&) = delete;
		void operator=(Renderer const&) = delete;

		void renderFrame();

	private:
		Renderer() {}

};

#endif
