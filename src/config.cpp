#include "platforms/platform.hpp"

#include <fstream>
#include <iostream>

#include "cvars.hpp"
#include "YamlNode.hpp"

using namespace std;

string getHomeDirectory() {
	return getenv("HOME");
}

void loadHomedirConfigurationFile() {
	ifstream ifs(getHomeDirectory().append("/.greyvar/config.yml"));
	string content ((istreambuf_iterator<char>(ifs) ), 
					 (istreambuf_iterator<char>()));

	auto config = YamlNode::fromString(content);

	for (auto p : config->attributes) {
		cvarSet(p.first, p.second, "config file");
	}
}
