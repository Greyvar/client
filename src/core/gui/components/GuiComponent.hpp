#pragma once

#include <string>

#include "../layout/LayoutConstraints.hpp"
#include "../layout/ResolvedPanelPosition.hpp"

class GuiComponent {
	public:
		GuiComponent(); 
		
		void setConstraints(LayoutConstraints* lc);

		int getMinimumHeight() const {
			return this->minimumHeight;
		}

		int getMinimumWidth() const {
			return this->minimumWidth;
		}
	
		ResolvedPanelPosition pos{};
		LayoutConstraints layoutConstraints{};

		std::string rendererFunc;

	protected:
		int minimumHeight = 100;
		int minimumWidth = 200;
};
