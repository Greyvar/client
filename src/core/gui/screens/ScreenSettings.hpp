#pragma once

#include "Screen.hpp"
#include "../components/Menu.hpp"

class ScreenSettings : public Screen {
	public:
		ScreenSettings() {
			this->setupComponents();
		}

		void setupComponents(); 

		void selectNextItem() override;
		void selectPrevItem() override;
		void executeCurrentItem() override;

	private:
		Menu* menu;
};
