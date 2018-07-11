#pragma once

#include <SDL2/SDL.h>
#include "ResCache.hpp"
#include "World.hpp"
#include "gui/utils/TextAlignment.hpp"

#define TILE_SIZE 64

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

		ResCache* resCache = new ResCache();
		SDL_Renderer* sdlRen;

		Renderer(Renderer const&) = delete;
		void operator=(Renderer const&) = delete;

		void renderFrame();

		int window_w = 0;
		int window_h = 0;

		FT_Library* freetypeLib = new FT_Library;

		int averageFps = 0;
	private:
		Renderer() {}

		SDL_Window* win;

};

void renderText(std::string text, int x, int y, SDL_Color color, bool canChangeColor, TextAlignment align, int fontSize);
void renderText(std::string text, int x, int y, SDL_Color color, bool canChangeColor, int size);
void renderRect(SDL_Color color, int x, int y, int w, int h);
void renderTextShadow(std::string text, int x, int y, TextAlignment alignment, int size);
void renderTextShadow(std::string text, int x, int y, int size);
void renderTextShadowWithBackground(std::string text, int x, int y, int size, SDL_Color bgColor, int offsetX);
void renderBackgroundSolidColor(SDL_Color color);
SDL_Color rgbaToSdlColor(int rgba);

void renderHud();
void renderPanel();
