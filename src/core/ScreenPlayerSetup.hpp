#pragma once

#include "Screen.hpp"

class ScreenPlayerSetup : public Screen {
	public:
		ScreenPlayerSetup() {
			this->setupComponents();
		}

		void setupComponents();
};
