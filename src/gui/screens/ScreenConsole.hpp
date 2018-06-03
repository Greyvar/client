#include <vector>

#include "Screen.hpp"

class ScreenConsole: public Screen {
	private:
		std::vector<string> consoleHistory; 
};
