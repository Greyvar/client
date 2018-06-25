#include <SDL2/SDL.h>

#include "gui/utils/TextAlignment.hpp"
#include "Renderer.hpp"

SDL_Texture* CreateTextureFromFT_Bitmap(SDL_Renderer* ren, const FT_Bitmap& bitmap, const SDL_Color& color);

using namespace std;

void renderText(std::string text, int x, int y, SDL_Color color, bool canChangeColor, TextAlignment align, int fontSize) {
	const FT_Face face = *Renderer::get().resCache->loadFont("DejaVuSansMono.ttf", fontSize);
	bool changeColor = false;

	if (align == CENTER) { // lazy center alignment with monospace text for now
		x -= (text.length() * 30) / 2;
	}

	for (char currentCharacter : text) {
		if (changeColor) {
			if (canChangeColor) {
				switch (currentCharacter) {
					case '0': color = {000, 000, 000, 255}; break; // black
					case '1': color = {255, 000, 000, 255}; break; // red
					case '2': color = {000, 255, 000, 255}; break; // green
					case '3': color = {255, 255, 000, 255}; break; // yellow
					case '4': color = {000, 000, 255, 255}; break; // blue
					case '5': color = {000, 255, 255, 255}; break; // cyan
					case '6': color = {255, 000, 255, 255}; break; // magenta
					case '7': color = {255, 255, 255, 255}; break; // white
					case '8': color = {255, 150, 000, 255}; break; // orange
					case '9': color = {100, 100, 100, 255}; break; // darkgrey
				}
			}

			changeColor = false;

			continue;
		} else if (currentCharacter == '^') {
			changeColor = true;
			continue;
		}

		FT_Load_Char(face, currentCharacter, FT_LOAD_RENDER);

		SDL_Texture* tex_glyph = CreateTextureFromFT_Bitmap(Renderer::get().sdlRen, face->glyph->bitmap, color);

		SDL_Rect dest;
		dest.x = x + (face->glyph->metrics.horiBearingX >> 6);
		dest.y = y - (face->glyph->metrics.horiBearingY >> 6);

		SDL_QueryTexture(tex_glyph, NULL, NULL, &dest.w, &dest.h);

		SDL_SetTextureBlendMode(tex_glyph, SDL_BLENDMODE_BLEND);
		SDL_RenderCopy(Renderer::get().sdlRen, tex_glyph, NULL, &dest);
		SDL_DestroyTexture(tex_glyph);

		x += (face->glyph->metrics.horiAdvance >> 6);

	}
}

void renderText(std::string text, int x, int y, SDL_Color color, bool canChangeColor, int size) {
	renderText(text, x, y, color, canChangeColor, LEFT, size);
}

void renderRect(SDL_Color color, int x, int y, int w, int h) {
	SDL_SetRenderDrawBlendMode(Renderer::get().sdlRen, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Renderer::get().sdlRen, color.r, color.g, color.b, color.a);

	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;

	SDL_RenderFillRect(Renderer::get().sdlRen, &pos);
}

void renderTextShadow(std::string text, int x, int y, TextAlignment alignment, int size) {
	int shadowOffset;

	if (size < 25) {
		shadowOffset = 1;
	} else {
		shadowOffset = 2;
	}

	renderText(text, x + shadowOffset, y + shadowOffset, {0, 0, 0, 255}, false, alignment, size);
	renderText(text, x, y, {255, 255, 255, 255}, true, alignment, size);
}

void renderTextShadow(std::string text, int x, int y, int size) {
	renderTextShadow(text, x, y, LEFT, size);
}

void renderTextShadowWithBackground(std::string text, int x, int y, int size, SDL_Color bgColor, int offsetX) {
	int pad = 5;

	renderRect(bgColor, x, y - ((size / 4) * 3), (offsetX * 2) + (text.length() * (size * .75)), size + (pad * 2));

	renderTextShadow(text, x + offsetX + (size / 3), y + (size * .25), size);
}

void renderBackgroundSolidColor(SDL_Color color) {
	renderRect(color, 0, 0, Renderer::get().window_w, Renderer::get().window_h);
}

SDL_Color rgbaToSdlColor(int rgba) {
	return {
		static_cast<uint8_t>((rgba & 0x0000ff)),
		static_cast<uint8_t>((rgba & 0x00ff00) >> 8),
		static_cast<uint8_t>((rgba & 0xff0000) >> 16),
		255
	};
}
