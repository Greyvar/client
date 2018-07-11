#pragma once

#include <vector>

#include "gui/components/GuiComponent.hpp"
#include "gui/layout/LayoutConstraints.hpp"

using namespace std;

class Screen {
	protected:
		void add(GuiComponent* comp, LayoutConstraints* lc);

	public:
		vector<GuiComponent*> components{};
};
