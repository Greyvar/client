#include "NetworkManager.hpp"
#include "GameState.hpp"
#include "Renderer.hpp"

using namespace std;

void handleKeypress(SDL_KeyboardEvent key) {
	const int speed = 4;

	switch (key.keysym.sym) {
		case SDLK_ESCAPE:
			std::cout << "escapppppe" << std::endl;

			SDL_Event quitEvent;
			quitEvent.type = SDL_QUIT;

			SDL_PushEvent(&quitEvent);
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
//			NetworkManager::sendHelo();
		default:
			std::cout << key.keysym.sym << std::endl;
	}
}


