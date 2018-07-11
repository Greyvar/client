#include <map>
#include <sstream>

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
		ss << "GridLineProperties. index:" << this->index << " size: " << this->size;

		return ss.str();
	}
};

class LayoutManager {
	public: 
		void doLayout(Screen* screen);
		void onChanged(Screen* screen);

		map<int, GridLineProperties> rowProperties;
		map<int, GridLineProperties> colProperties;

};
