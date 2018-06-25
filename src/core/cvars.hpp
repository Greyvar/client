#pragma once

#include <map>

using namespace std;

void cvarInit();

void cvarSet(string key, string val, string source);
void cvarSet(string key, string val);
void cvarSetb(string key, bool val);
void cvarSeti(string key, int val);
void cvarSeti(string key, int val, string from);

string cvarGet(string key);
bool cvarGetb(string key);
int cvarGeti(string key);
int cvarGeti(string key, int def);

bool cvarIsset(string key);

