enum HidInputDeviceType {
	KEYBOARD,
	GAMEPAD,
	TOUCH,
	MOUSE
};

union HidInputDevicePointer {
	SDL_GameController* gamepad;
	size_t keyboard;
	size_t touchme;
	size_t mouse;
};

class HidInputDevice {
	public:
	HidInputDeviceType type;
	HidInputDevicePointer device;
};
