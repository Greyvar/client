#pragma once

#include "Screen.hpp"

class ScreenServerBrowser: public Screen {
	public:
		ScreenServerBrowser() {
			this->setupComponents();
		}

		void setupComponents();
		void executeCurrentItem() override;
};
