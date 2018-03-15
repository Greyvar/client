#include "GameState.hpp"
#include "Renderer.hpp"

#include <SDL2/SDL_image.h>

#include <ft2build.h>
#include FT_FREETYPE_H

SDL_Texture* CreateTextureFromFT_Bitmap(SDL_Renderer* ren, const FT_Bitmap& bitmap, const SDL_Color& color);

void renderBackground(World* world) {
	const int TILE_SIZE = 64;

	int w = world->tileGrid->w * TILE_SIZE;
	int h = world->tileGrid->h * TILE_SIZE;

	int padx = (Renderer::get().window_w - w) / 2;
	int pady = (Renderer::get().window_h - h) / 2;

	for (int row = 0; row < world->tileGrid->h; row++) {
		for (int col = 0; col < world->tileGrid->w; col++) {
			Tile* tile = world->tileGrid->get(row, col);

			SDL_Rect pos;


			pos.x = padx + (col * TILE_SIZE);
			pos.y = pady + (row * TILE_SIZE);
			pos.w = TILE_SIZE;
			pos.h = TILE_SIZE;

			SDL_RenderCopy(Renderer::get().sdlRen, Renderer::get().resCache->loadTile(tile->textureName), NULL, &pos);
		}
	}
}

void renderEntities(World* world) {
	for (auto e : world->entityGrid->entities) {
		SDL_RenderCopy(Renderer::get().sdlRen, Renderer::get().resCache->loadEntity(e->textureName), NULL, e->pos);
	}
}

void renderText(World* world, std::string text, int x, int y, SDL_Color color, bool canChangeColor) {
	const FT_Face face = *Renderer::get().resCache->loadFont("DejaVuSansMono.ttf");

	bool changeColor = false;

	std::cout << "Font: " << (face) << endl;

	for (char currentCharacter : text) {
		if (changeColor) {
			if (canChangeColor) {
				switch (currentCharacter) {
					case '1': color = {255, 000, 000}; break;
					case '2': color = {000, 255, 000}; break;
					case '3': color = {000, 000, 255}; break;
					case '7': color = {255, 255, 255}; break;
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

void renderTextShadow(World* world, std::string text, int x, int y) {
	renderText(world, text, x + 2, y + 2, {0, 0, 0}, false);
	renderText(world, text, x, y, {255, 255, 255}, true);
}

void Renderer::renderFrame() {
	std::cout << "render frame ----------------------" << std::endl;

	SDL_Renderer* ren = Renderer::get().sdlRen;
	SDL_RenderClear(ren);

	World* world = GameState::get().world;

	renderBackground(world);
	renderEntities(world);
	renderTextShadow(world, "^1Greyvar 2.0", 100, 50);
	renderTextShadow(world, "^3My name is ^7James", 100, 100);

	SDL_RenderPresent(ren);
}


