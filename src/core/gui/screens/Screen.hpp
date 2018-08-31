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
		std::string getPreviousScreenName() {
			return this->previousScreenName;
		}

		virtual void selectNextItem();
		virtual void selectPrevItem();
		virtual void executeCurrentItem();

		void onMouseMoved(const int x, const int y);
		void onClick(const int x, const int y);

		GuiComponent* getComponentAt(const int x, const int y) const;

		GuiComponent* focussedComponent = nullptr;

		vector<GuiComponent*> components{};

		std::string previousScreenName{};
};
