#pragma once

#include <boleas/Screen.hpp>

class ScreenAbout : public Screen {
	public:
		ScreenAbout() {
			this->setupComponents();
		}

		void setupComponents();
};
