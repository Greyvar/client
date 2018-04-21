#pragma once

#include <map>

void cvarInit();

void cvarSet(std::string key, std::string val);
void cvarSetb(std::string key, bool val);

std::string cvarGet(std::string key);
bool cvarGetb(std::string key);

bool cvarIsset(std::string key);

