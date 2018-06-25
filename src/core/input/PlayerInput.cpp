#include <queue>
#include <iostream>

#include "PlayerInput.hpp"
#include "input/1_bindings/common.hpp"
#include "common.hpp"

using namespace std;

PlayerInput::PlayerInput(LocalPlayer* localPlayer, HidInputGesture hidInputGesture) {
	this->localPlayer = localPlayer;
	this->hidInputGesture = hidInputGesture;

	this->queueForBinding();
}

void PlayerInput::queueForBinding() {
	if (this->queuedForBinding) {
		throw "Already queued.";
	}

	this->queuedForBinding = true;

	unboundPlayerInputQueue.push(this);
}

