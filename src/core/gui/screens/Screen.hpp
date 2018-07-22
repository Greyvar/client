#pragma once

#include "gui/components/GuiComponent.hpp"
#include "gui/layout/LayoutConstraints.hpp"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Screen {
	protected:
		void add(GuiComponent* comp, LayoutConstraints* lc);

		~Screen() {
			std::cout << "delete screen " << std::endl;

			for (auto& comp : this->components) {
				delete(comp);
			}

			this->components.clear();
		}

	public:
		virtual void selectNextItem();
		virtual void selectPrevItem();
		virtual void executeCurrentItem();

		vector<GuiComponent*> components{};
};
