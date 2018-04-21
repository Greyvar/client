#include <iostream>
#include <map>

#include "cvars.hpp"

using namespace std;

map<string, string> cvars;

bool cvarIsset(string key) {
	return ::cvars.count(key) == 1;
}

void cvarSet(string key, string val) {
	cout << "Set cvar " << key << " = " << val << endl;

	::cvars[key] = val;
}

void cvarSetb(string key, bool val) {
	if (val) {
		cvarSet(key, "1");
	} else {
		cvarSet(key, "0");
	}
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

void cvarInit() {
	cvarSet("nickname", "unamed.player");
	cvarSetb("bind_keyboard", true);
}
