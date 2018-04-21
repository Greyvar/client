#pragma once

#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class YamlNode {
	private: 
		map<string, string> attributes;
		map<string, YamlNode*> children;
		vector<YamlNode*> items;

	public:
		YamlNode* parent = NULL;

		YamlNode* child(string name);
		YamlNode* attr(string name, string value);
		YamlNode* attr(string name, int value);

		string attr(string name);
		uint32_t attri(string name);
		bool attrb(string name);

		YamlNode* list(string title);
		YamlNode* listitem();

		static YamlNode* fromStringstream(stringstream input);
		static YamlNode* fromString(string input);
		string toString();
		string toString(int level);
		string toString(int level, bool skipLeading);
};

