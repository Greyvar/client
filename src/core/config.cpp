#include "platforms/platform.hpp"

#include "cvars.hpp"
#include "YamlNode.hpp"

#include <fstream>
#include <iostream>

using std::string;

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

	delete(config);
}
