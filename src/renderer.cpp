#include <chrono>

#include <SDL2/SDL_image.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GameState.hpp"
#include "Renderer.hpp"
#include "gui/Gui.hpp"
#include "cvars.hpp"

void renderGridTiles(World* world) {
	int windowWidth = 2 * floor(Renderer::get().window_w / 2);
	int windowHeight = 2 * floor(Renderer::get().window_h / 2);

//	int tileRenderLength = std::min(windowWidth, windowHeight) / 16;
	int tileRenderLength = TILE_SIZE;

	int gridTilesWidth = world->tileGrid->w * tileRenderLength;
	int gridTilesHeight = world->tileGrid->h * tileRenderLength;

	int padx = (windowWidth - gridTilesWidth) / 2;
	int pady = (windowHeight - gridTilesHeight) / 2;

	for (int row = 0; row < world->tileGrid->h; row++) {
		for (int col = 0; col < world->tileGrid->w; col++) {
			Tile* tile = world->tileGrid->get(row, col);

			SDL_Rect pos;


			pos.x = padx + (col * tileRenderLength);
			pos.y = pady + (row * tileRenderLength);
			pos.w = tileRenderLength;
			pos.h = tileRenderLength;

			int rot = tile->texRot;

			int flip = SDL_FLIP_NONE;
			if (tile->texVFlip && tile->texHFlip) {
				flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
			} else if (tile->texVFlip) {
				flip = SDL_FLIP_VERTICAL;
			} else if (tile->texHFlip) {
				flip = SDL_FLIP_HORIZONTAL;
			}

			SDL_RenderCopyEx(Renderer::get().sdlRen, Renderer::get().resCache->loadTile(tile->textureName), NULL, &pos, rot, NULL, (SDL_RendererFlip)flip);
		}
	}
}

void renderGridEntities(World* world) {
	int windowWidth = 2 * floor(Renderer::get().window_w / 2);
	int windowHeight = 2 * floor(Renderer::get().window_h / 2);

	int tileRenderLength = TILE_SIZE;

	int gridTilesWidth = world->tileGrid->w * tileRenderLength;
	int gridTilesHeight = world->tileGrid->h * tileRenderLength;

	int padx = (windowWidth - gridTilesWidth) / 2;
	int pady = (windowHeight - gridTilesHeight) / 2;

	for (auto p : world->entityGrid->entities) {
		auto e = p.second;
		SDL_Rect r; 
		r.x = padx + (e->pos->x * 4);
		r.y = pady + (e->pos->y * 4);
		r.w = e->pos->w;
		r.h = e->pos->h;

		SDL_Texture* tex = Renderer::get().resCache->loadEntity(e->textureName, e->primaryColor);
		
		SDL_RenderCopy(Renderer::get().sdlRen, tex, NULL, &r);

	}
}

void renderMenu() {
	renderBackgroundSolidColor({130, 130, 130});
	renderTextShadow("^9Greyvar 2.0", 15, 50, 36);
//	renderTextShadow("^7" + GameState::get().gui->subtitle, 20, 80, 16);

/**
	for (unsigned int i = 0; i < GameState::get().gui->currentMenu->size(); i++) {
		std::string itemText = GameState::get().gui->currentMenu->at(i)->text;

		if (i == GameState::get().gui->currentlySelectedMenuItem) {
			itemText.insert(0, "^5");
		}

		renderTextShadow(itemText, 20, 160 + (i * 60), LEFT, 24);
	}
*/

	using namespace std::chrono;
	milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

	SDL_Rect pos;
	pos.w = pos.h = 64;
	pos.x = (Renderer::get().window_w / 2) + (sin(ms.count() * .0005) * 250);
	pos.y = Renderer::get().window_h - pos.h + 4;

	SDL_Texture* texPlayer = Renderer::get().resCache->loadEntity("playerBob.png");

	SDL_RenderCopy(Renderer::get().sdlRen, texPlayer, NULL, &pos);

//	SDL_SetTextureColorMod(texPlayer, 255, 90, 90);

//	SDL_RenderCopy(Renderer::get().sdlRen, texPlayer, NULL, &pos);
}

void renderConsole() {
	renderBackgroundSolidColor({66, 66, 66});
	renderTextShadow("^9Greyvar console", 15, 50, 36);
	renderTextShadow("This is the console.", 15, 80, 16);

/**
	for (unsigned int i = 0; i < GameState::get().gui->consoleHistory.size(); i++) {
		renderTextShadow(GameState::get().gui->consoleHistory.at(i), 50, 50 + (i * 20), 24);
	}
*/
}

void renderUiMessages() {
	uint32_t index = 0;

	for (auto it : GameState::get().gui->messages) {
		renderTextShadow(it.second, 50, (Renderer::get().window_h - 80) - (index * 50), 24);
		index++;
	}
}

void renderFps() {
	if (cvarGetb("r_fps")) {
		renderText("FPS: " + to_string(Renderer::get().averageFps), Renderer::get().window_w - 0, 20, {230, 230, 230}, false, CENTER, 16);
	}
}

void Renderer::renderFrame() {
	//std::cout << "render frame ----------------------" << std::endl;

	SDL_Renderer* ren = Renderer::get().sdlRen;
	SDL_RenderClear(ren);

	World* world = GameState::get().world;

	switch (GameState::get().gui->scene) {
		case MENU:
			renderMenu();
			break;
		case CONSOLE:
			renderConsole();
			break;
		case PLAY:
			renderGridTiles(world);
			renderGridEntities(world);
			renderHud();
			break;
		case NONE:
			renderBackgroundSolidColor({30, 30, 30});
	}

	renderFps();	
	renderUiMessages();

	SDL_RenderPresent(ren);
}


