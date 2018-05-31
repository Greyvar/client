#pragma once

#include "RemotePlayer.hpp"
#include "input/InputDevice.hpp"

class LocalPlayer {
	public: 
		RemotePlayer* remote;
		InputDevice inputDevice;
};
