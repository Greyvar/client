#pragma once

#include "Screen.hpp"

class ScreenSplash : public Screen {
	public: 
		ScreenSplash() {
			this->setupComponents();
		}

		void setupComponents();
};
