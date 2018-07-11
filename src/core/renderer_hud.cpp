#include "GameState.hpp"
#include "Renderer.hpp"
#include "LocalPlayer.hpp"

void renderHudPlayer(LocalPlayer* lp, int x, int y, int fontSize, bool firstPlayer) {
	string text = lp->username;

	SDL_Color playerColor{};
	uint8_t backgroundIntensity;

	if (lp->remote == nullptr) {
		playerColor = {255, 255, 255, 200};
		backgroundIntensity = 100;
	} else {
		playerColor = rgbaToSdlColor(lp->remote->ent->primaryColor);
		backgroundIntensity = 200;
	}
	
	renderRect(playerColor, x - (fontSize * .5), y - (fontSize * 1), fontSize / 2, fontSize + (5 * 2) + (fontSize / 2));
	renderRect({100, 100, 100, backgroundIntensity}, x, y - (fontSize * 1), 172, 48);
	renderTextShadow(text, x + 40, y, fontSize);

	SDL_Rect inputDeviceIconPos{};
	inputDeviceIconPos.x = x + 5;
	inputDeviceIconPos.y = (y - fontSize) + (5 * 1.5);
	inputDeviceIconPos.w = 32;
	inputDeviceIconPos.h = 32;

	SDL_Texture* texInputDeviceIcon;

	int smallTextOffset = 20;
	
	switch (lp->inputDevice.type) {
		case GAMEPAD:
			if (firstPlayer) {
				texInputDeviceIcon = Renderer::get().resCache->loadHud("gamepadKeyboard.png");

				renderTextShadow("Press Start/Enter", x + 40, y + smallTextOffset, fontSize / 2);
			} else {
				texInputDeviceIcon = Renderer::get().resCache->loadHud("gamepad.png");
				renderTextShadow("Press Start", x + 40, y + smallTextOffset, fontSize / 2);
			}

			break;
		case KEYBOARD:
			texInputDeviceIcon = Renderer::get().resCache->loadHud("keyboard.png");
			renderTextShadow("Press Enter", x + 40 , y + smallTextOffset, fontSize / 2);
			break;
		default:
			texInputDeviceIcon = Renderer::get().resCache->loadHud("question.png");
			break;
	}
	
	SDL_RenderCopy(Renderer::get().sdlRen, texInputDeviceIcon, nullptr, &inputDeviceIconPos);
}

void renderHud() {
	int fontSize = 24;
	int y = Renderer::get().window_h - 30;
	int x = -150;

	for (auto lp : GameState::get().getLocalPlayers()) {
		bool firstPlayer = lp == GameState::get().getFirstLocalPlayer();

		x += 200;

		renderHudPlayer(lp, x, y, fontSize, firstPlayer);
	}

	renderTextShadowWithBackground("Players: ^5" + to_string(GameState::get().getRemotePlayerCount()), Renderer::get().window_w - 200, y, fontSize, {100, 100, 100, 255}, 0);
}


