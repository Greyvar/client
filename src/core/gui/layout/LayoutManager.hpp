#include <map>
#include <sstream>

#include "cvars.hpp"
#include "../screens/Screen.hpp"

struct GridLineProperties {
	int weight = 0;
	int size = 0;
	int offset = 0;
	int index = 0;
	int largestComponentSize = 0;

	GridLineProperties() {}

	std::string str() {
		stringstream ss;

		return ss.str();
	}
};

class LayoutManager {
	public: 
		void doLayout(Screen* screen);
		void onChanged(Screen* screen);
		void debugLayoutFinished();

		map<int, GridLineProperties> rowProperties;
		map<int, GridLineProperties> colProperties;

};
