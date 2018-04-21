#pragma once

#include "0_hid/HidInput.hpp"
#include "2_actions/ActionInput.hpp"
#include "LocalPlayer.hpp"

class PlayerInput {
	public:
		PlayerInput(LocalPlayer* localPlayer);
		PlayerInput(LocalPlayer* localPlayer, HidInput hidInput);

		void hidInputQueue(HidInput hidInput);

		LocalPlayer* localPlayer;
		HidInput hidInput;
		ActionInput actionInput;

		void queue();

	private:
		bool queued = false;
};

