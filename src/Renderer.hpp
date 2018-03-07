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

		static void set(SDL_Window* win, SDL_Renderer* renderer) {
			get().sdlRen = renderer;
			get().win = win;
		}

		SDL_Window* getWindow() {
			return this->win;
		}

		TextureCache* textureCache = new TextureCache();
		SDL_Renderer* sdlRen;

		Renderer(Renderer const&) = delete;
		void operator=(Renderer const&) = delete;

		void renderFrame();

		int window_w = 0;
		int window_h = 0;

	private:
		Renderer() {}

		SDL_Window* win;

};

#endif
