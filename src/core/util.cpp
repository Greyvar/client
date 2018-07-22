#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>

#include "cvars.hpp"

using std::string;

stringstream readFile(const string& filename) {
	string line;
	stringstream out; 	
	ifstream inFile;
	
	inFile.open(filename);

	while (getline(inFile, line)) {
		cout << "read line: " << line << endl;

		out << line << endl;
	}

	inFile.close();

	return out;
}

void parseArguments(int argc, char* argv[]) {
	enum {
		ANY,
		CVAR,
	} nextArgumentExpected = ANY;

	string last{};

	for (uint32_t i = 0; i < argc; i++) {
		string current = argv[i];

		switch (nextArgumentExpected) {
			case ANY:	
				if (current[0] == '-') {
					nextArgumentExpected = CVAR;
				}

				if (current[0] == '+') {
					cvarSet(current.substr(1), "1", "command line, +1 syntax");
					nextArgumentExpected = ANY;
				}

				break;
			case CVAR:
				cvarSet(last.substr(1), current, "command line");

				nextArgumentExpected = ANY;
				break;
		}

		last = current;
	}
}

