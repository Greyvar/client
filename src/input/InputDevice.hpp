enum InputDeviceType {
	KEYBOARD,
	GAMEPAD,
	TOUCH
};

union InputDevicePointer {
	SDL_GameController* gamepad;
	size_t keyboard;
	size_t touchme;
};

class InputDevice {
	public:
	InputDeviceType type;
	InputDevicePointer device;
};
