#include "GameState.hpp"
#include "../PlayerInput.hpp"

void toucheytouchey() {
	PlayerInput* phi = new PlayerInput(GameState::get().getFirstLocalPlayer());
	phi->hidInputQueue(KEY_TILDE);
}
