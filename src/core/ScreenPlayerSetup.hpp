#pragma once

#include <boleas/gui/screens/Screen.hpp>

class ScreenPlayerSetup : public Screen {
	public:
		ScreenPlayerSetup() {
			this->setupComponents();
		}

		void setupComponents();
};
