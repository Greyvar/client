#include <chrono>

#include <SDL2/SDL_image.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GameState.hpp"
#include "Renderer.hpp"
#include "Ui.hpp"
#include "cvars.hpp"

SDL_Texture* CreateTextureFromFT_Bitmap(SDL_Renderer* ren, const FT_Bitmap& bitmap, const SDL_Color& color);


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
	for (auto e : world->entityGrid->entities) {
		SDL_RenderCopy(Renderer::get().sdlRen, Renderer::get().resCache->loadEntity(e->textureName), NULL, e->pos);
	}
}

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
					case '0': color = {000, 000, 000}; break; // black
					case '1': color = {255, 000, 000}; break; // red
					case '2': color = {000, 255, 000}; break; // green
					case '3': color = {255, 255, 000}; break; // yellow
					case '4': color = {000, 000, 255}; break; // blue
					case '5': color = {000, 255, 255}; break; // cyan
					case '6': color = {255, 000, 255}; break; // magenta
					case '7': color = {255, 255, 255}; break; // white
					case '8': color = {255, 150, 000}; break; // orange
					case '9': color = {100, 100, 100}; break; // darkgrey
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
	renderText(text, x, y, color, LEFT, size);
}

void renderTextShadow(std::string text, int x, int y, TextAlignment alignment, int size) {
	int shadowOffset;

	if (size < 25) {
		shadowOffset = 1;
	} else {
		shadowOffset = 2;
	}

	renderText(text, x + shadowOffset, y + shadowOffset, {0, 0, 0}, false, alignment, size);
	renderText(text, x, y, {255, 255, 255}, true, alignment, size);
}

void renderTextShadow(std::string text, int x, int y, int size) {
	renderTextShadow(text, x, y, LEFT, size);
}

void renderBackgroundSolidColor(SDL_Color color) {
	SDL_SetRenderDrawColor(Renderer::get().sdlRen, color.r, color.g, color.b, color.a);

	SDL_Rect bg;
	bg.x = 0;
	bg.y = 0;
	bg.w = Renderer::get().window_w;
	bg.h = Renderer::get().window_h;

	SDL_RenderFillRect(Renderer::get().sdlRen, &bg);
}

void renderMenu() {
	renderBackgroundSolidColor({130, 130, 130});
	renderTextShadow("^9Greyvar 2.0", 15, 50, 36);
	renderTextShadow("^7" + GameState::get().ui->subtitle, 20, 80, 16);

	for (unsigned int i = 0; i < GameState::get().ui->currentMenu->size(); i++) {
		std::string itemText = GameState::get().ui->currentMenu->at(i)->text;

		if (i == GameState::get().ui->currentlySelectedMenuItem) {
			itemText.insert(0, "^5");
		}

		renderTextShadow(itemText, 20, 160 + (i * 60), LEFT, 24);
	}

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

	for (unsigned int i = 0; i < GameState::get().ui->consoleHistory.size(); i++) {
		renderTextShadow(GameState::get().ui->consoleHistory.at(i), 50, 50 + (i * 20), 24);
	}
}

void renderUiMessages() {
	uint32_t index = 0;

	for (auto it : GameState::get().ui->messages) {
		renderTextShadow(it.second, 50, (Renderer::get().window_h - 50) - (index * 50), 24);
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

	switch (GameState::get().ui->scene) {
		case MENU:
			renderMenu();
			break;
		case CONSOLE:
			renderConsole();
			break;
		case PLAY:
			renderGridTiles(world);
			renderGridEntities(world);
			break;
		case NONE:
			renderBackgroundSolidColor({30, 30, 30});
	}

	renderFps();	
	renderUiMessages();

	SDL_RenderPresent(ren);
}


