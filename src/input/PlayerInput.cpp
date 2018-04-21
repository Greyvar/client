#include <queue>

#include "PlayerInput.hpp"
#include "input/1_bindings/common.hpp"
#include "common.hpp"

using namespace std;

PlayerInput::PlayerInput(LocalPlayer* localPlayer) {
	this->localPlayer = localPlayer;
	this->hidInput = HID_NOOP;
}

PlayerInput::PlayerInput(LocalPlayer* localPlayer, HidInput hidInput) {
	this->localPlayer = localPlayer;
	this->hidInput = hidInput;

	this->queue();
}

void PlayerInput::hidInputQueue(HidInput hidInput) {
	this->hidInput = hidInput;
	this->queue();
}

void PlayerInput::queue() {
	if (this->queued) {
		throw "Already queued.";
	}

	this->queued = true;

	unboundPlayerInputQueue.push(this);
}
