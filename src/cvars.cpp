#include <iostream>
#include <map>

#include "cvars.hpp"

using namespace std;

map<string, string> cvars;

bool cvarIsset(string key) {
	return ::cvars.count(key) == 1;
}

void cvarSet(string key, string val, string source) {
	if (source.size() > 0) {
		source = "(from " + source + ") ";
	}

	cout << "Set cvar " << source << key << " = " << val << endl;

	::cvars[key] = val;
}

void cvarSet(string key, string val) {
	cvarSet(key, val, "");
}

void cvarSetb(string key, bool val, string source) {
	if (val) {
		cvarSet(key, "1", source);
	} else {
		cvarSet(key, "0", source);
	}
}

void cvarSetb(string key, bool val) {
	cvarSetb(key, val, "");
}

string cvarGet(string key) {
	if (cvarIsset(key)) {
		return ::cvars[key];
	} else {
		return "";
	}
}

bool cvarGetb(string key) {
	string s = cvarGet(key);

	if (s == "") {
		return 0;
	}

	try {
		return stoi(s.c_str());
	} catch (...) {
		cout << "cvar, number expected, got >" << s << "<" << endl;
		return 0;
	}
}

int cvarGeti(string key) {
	return stoi(cvarGet(key));
}

void cvarSeti(string key, int val) {
	cvarSeti(key, val, "");
}

void cvarSeti(string key, int val, string from) {
	cvarSet(key, to_string(val), from);
}

void cvarInit() {
	string def = "defaults";

	cvarSet("nickname", "unamed.player", def);
	cvarSetb("bind_keyboard", true, def);
	cvarSeti("snd_channel_ui_volume", 100, def);
}
