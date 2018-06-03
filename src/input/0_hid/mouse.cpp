#include "GameState.hpp"
#include "../PlayerInput.hpp"

// Mice input events will always use the first local player.

void mouseButtonClicked() {
	new PlayerInput(GameState::get().getFirstLocalPlayer(), MOUSE_CLICK_LEFT);
}
