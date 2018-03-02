#include "GameState.hpp"
#include "Renderer.hpp"
#include <SDL2/SDL_image.h>

void renderBackground(World* world) {
	for (int row = 0; row < world->tileGrid->h; row++) {
		for (int col = 0; col < world->tileGrid->w; col++) {
			Tile* tile = world->tileGrid->get(row, col);

			SDL_Rect pos;

			const int TILE_SIZE = 64;

			pos.x = col * TILE_SIZE;
			pos.y = row * TILE_SIZE;
			pos.w = TILE_SIZE;
			pos.h = TILE_SIZE;

			SDL_RenderCopy(Renderer::get().sdlRen, Renderer::get().textureCache->loadTile(tile->textureName), NULL, &pos);
		}
	}
}

void renderEntities(World* world) {
	for (auto e : world->entityGrid->entities) {

		SDL_RenderCopy(Renderer::get().sdlRen, Renderer::get().textureCache->loadEntity(e->textureName), NULL, e->pos);
	}
}

void Renderer::renderFrame() {
	SDL_Renderer* ren = Renderer::get().sdlRen;
	SDL_RenderClear(ren);

	SDL_RenderCopy(ren, Renderer::get().textureCache->load(string("logo.bmp")), NULL, NULL);

	World* world = GameState::get().world;

	renderBackground(world);
	renderEntities(world);

	SDL_RenderPresent(ren);
}


