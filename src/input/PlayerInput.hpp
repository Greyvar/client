#pragma once

#include <iostream>

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

		friend ostream& operator<<(ostream& out, const PlayerInput& pi) {
			return out << "PI {hid: ___ , action: ___ }" << endl;
		}

	private:
		bool queued = false;
};

