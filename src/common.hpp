#pragma once

#include <sstream>

std::stringstream readFile(std::string filename);

// BEGIN https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

#include <algorithm>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// END https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

enum SoundChannel {
	UI = 1,
	PLAYER = 2,
};


void playSound(std::string filename, SoundChannel ch);
