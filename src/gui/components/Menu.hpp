#pragma once

#include <iostream>
#include <vector>

#include "Sound.hpp"
#include "GuiComponent.hpp"
#include "MenuItem.hpp"

using namespace std;

class Menu: public GuiComponent {
	public:
		void add(string title) {
			this->items.push_back(new MenuItem(title));
		}

		void selectPrevMenuItem() {
			if (this->currentlySelectedMenuItem > 0) {
				this->currentlySelectedMenuItem--;

				playSound("interface/interface1.wav", UI);
			} else {
				playSound("interface/interface2.wav", UI);
			}
		}

		void selectNextMenuItem() {
			if (this->currentlySelectedMenuItem < this->items.size() - 1) {
				this->currentlySelectedMenuItem++;

				playSound("interface/interface1.wav", UI);
			} else {
				playSound("interface/interface2.wav", UI);
			}
		}

		void executeCurrentMenuItem() {
			playSound("interface/interface3.wav", UI);

			MenuItem* item = this->items.at(this->currentlySelectedMenuItem);

			item->action();
		}
	private:

		std::vector<MenuItem*> items;
		
		unsigned int currentlySelectedMenuItem = 0;

};
