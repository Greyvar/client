#pragma once

#include <string>

#include "../layout/LayoutConstraints.hpp"
#include "../layout/ResolvedPanelPosition.hpp"

class GuiComponent {
	public:
		GuiComponent(); 

		void setConstraints(LayoutConstraints* lc);
	
		ResolvedPanelPosition pos{};
		LayoutConstraints layoutConstraints{};

		std::string rendererFunc;
};
