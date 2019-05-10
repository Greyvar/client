#include <map>

#include "Renderer.hpp"
#include "LayoutManager.hpp"

void LayoutManager::onChanged(Screen* screen) {
	this->rowProperties.clear();
	this->colProperties.clear();

	int numCols = 1;
	int numRows = 1;

	for (auto comp : screen->components) {
		if (comp->layoutConstraints.x > numCols) {
			numCols = comp->layoutConstraints.x; 
		}

		if (comp->layoutConstraints.y > numRows) {
			numRows = comp->layoutConstraints.y;
		}
	}

	for (int row = 0; row < numRows + 1; row++) {
		rowProperties[row].index = row;
	}

	for (int col = 0; col < numCols + 1; col++) {
		colProperties[col].index = col;
	}
}

void LayoutManager::debugLayoutFinished() {
	if (!cvarGetb("debug_gui_layout")) {
		return;
	}

	cout << "Layout finished" << endl;

	for (size_t row = 0; row < this->rowProperties.size(); row++) {
		cout << "row " << row << " " << this->rowProperties[row].str() << endl;
	}

	for (size_t col = 0; col < this->colProperties.size(); col++) {
		cout << "col " << col << " " << this->colProperties[col].str() << endl;
	}
}

void LayoutManager::doLayout(Screen* screen) {
	int windowPadding = 32;

	cout << "Doing layout, rows:" << this->rowProperties.size() << "\tcols:" << this->colProperties.size() << endl;

	//  Apply layout to components
	
	int equalRowHeight = Renderer::get().window_h / this->rowProperties.size();
	int euqlaColWidth = Renderer::get().window_w / this->colProperties.size();

	int sparePixelHeight = 0;
	
	for (size_t row = 0; row < this->rowProperties.size(); row++) {
	}

	int sparePixelWidth;

	this->debugLayoutFinished();
		
	for (auto comp : screen->components) {
		comp->pos.x = windowPadding + this->colProperties[comp->pos.x].offset;
		comp->pos.y = windowPadding + this->rowProperties[comp->pos.y].offset;
	}
}

