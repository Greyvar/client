#pragma once

class LayoutConstraints {
	public:
		int row = 0;
		int col = 0;
		int rowWeight = 0;
		int colWeight = 0;
		
		enum {
			NORTH,
			EAST,
			SOUTH,
			WEST
		} alignment; 
};
