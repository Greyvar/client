#ifndef H_YAML
#define H_YAML

#include <string>
#include <map>
#include <vector>

using namespace std;

class YamlNode {
	private: 
		map<string, string> attributes;
		map<string, YamlNode*> children;
		vector<YamlNode*> items;

	public:
		YamlNode* child(string name);
		void attr(string name, string value);
		void attr(string name, int value);
		string attr(string name);
		YamlNode* item();

		static YamlNode* fromString(string input);
		string toString();
		string toString(int level);
};

#endif
