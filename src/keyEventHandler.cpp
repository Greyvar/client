#include "NetworkManager.hpp"
#include "GameState.hpp"
#include "Renderer.hpp"

using namespace std;

void handleKeypress(SDL_KeyboardEvent key) {
	const int speed = 4;
	
	UserInterface* ui = GameState::get().ui;

	switch (key.keysym.sym) {
		case SDLK_ESCAPE:
			std::cout << "escapppppe" << std::endl;

			SDL_Event quitEvent;
			quitEvent.type = SDL_QUIT;

			SDL_PushEvent(&quitEvent);
			break;
		case SDLK_UP:
			if (ui->state == MENU) {
				ui->selectPrevMenuItem();
			}

			break;
		case SDLK_DOWN:
			if (ui->state == MENU) {
				ui->selectNextMenuItem();
			}

			break;
		case SDLK_RETURN:
			if (ui->state == MENU) {
				ui->executeCurrentMenuItem();
			}

			break;
		case SDLK_TAB:
			ui->toggleMenu();

			break;
		case SDLK_w:
			GameState::get().getPlayer(0)->pos->y -= speed;
			break;
		case SDLK_s:
			GameState::get().getPlayer(0)->pos->y += speed;
			break;
		case SDLK_a:
			GameState::get().getPlayer(0)->pos->x -= speed;
			break;
		case SDLK_d:
			GameState::get().getPlayer(0)->pos->x += speed;
			break;
		case SDLK_F10:
			NetworkManager::get().connectToServer();
			NetworkManager::get().sendHelo();
			break;
		case SDLK_BACKQUOTE:
			ui->toggleConsole();

			break;
		default:
			std::cout << "key: " << key.keysym.sym << std::endl;
	}
}
