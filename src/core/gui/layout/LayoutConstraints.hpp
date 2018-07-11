#pragma once

class LayoutConstraints {
	public:
		int x = 0;
		int y = 0;
		int weightX = 0;
		int weightY = 0;
		int padx = 0;
		int pady = 0;
		
		enum {
			NORTH,
			EAST,
			SOUTH,
			WEST
		} alignment; 
};
