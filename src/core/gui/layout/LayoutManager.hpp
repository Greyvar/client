#include "../screens/Screen.hpp"
#include "GridCell.hpp"
#include "GridLineProperties.hpp"

#include <map>

class LayoutManager {
	public: 
		void doLayout(Screen* screen);
		void onChanged(Screen* screen);

		void debugLayout() const;
		void applyLayoutToComponents(Screen* screen);

	private:
		map<int, GridLineProperties> rowProperties;
		map<int, GridLineProperties> colProperties;
		map<int, map<int, GridCell*> > gridCells{};
	
		int windowPadding = 32;
};
