#include "YamlNode.hpp"

#include <sstream>

using namespace std;

YamlNode* YamlNode::fromString(string input) {
	YamlNode* n = new YamlNode();

	return n;
}

void YamlNode::attr(string name, int value) {
	this->attributes[name] = to_string(value);
}

void YamlNode::attr(string name, string value) {
	this->attributes[name] = value;
}

string YamlNode::attr(string name) {
	return this->attributes[name];
}

YamlNode* YamlNode::child(string name) {
	auto child = new YamlNode();

	this->children[name] = child;

	return child;
}

string YamlNode::toString() {
	return this->toString(0);
}

string YamlNode::toString(int level) {
	stringstream out;

	for (auto pair : this->attributes) {
		out << string(level, '\t') << pair.first << ": " << pair.second << "\n";
	}

	for (auto pair : this->children) {
		out << string(level, '\t') << pair.first << ": \n";
		out << pair.second->toString(level + 1);
	}

	for (auto i : this->items) {
		out << i->toString(level + 1);
	}

	return out.str();
}

YamlNode* YamlNode::item() {
	auto i = new YamlNode();

	this->items.push_back(i);

	return i;
}
