#pragma once

#include "../layout/LayoutConstraints.hpp"

class GuiComponent {
	public:

	void setConstraints(LayoutConstraints lc) {
		this->lc = lc;
	};

	LayoutConstraints getConstraints() {
		return this->lc; 
	}

	private: 

	LayoutConstraints lc;
};
