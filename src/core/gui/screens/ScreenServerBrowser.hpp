#include "Screen.hpp"

class ScreenServerBrowser: public Screen {
	public:
		ScreenServerBrowser() {
			this->setupComponents();
		}

		void setupComponents();
};
