#pragma once

#include "Screen.hpp"

class ScreenAbout : public Screen {
	public:
		ScreenAbout() {
			this->setupComponents();
		}

		void setupComponents();
};
