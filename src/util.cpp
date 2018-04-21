#include <fstream>
#include <sstream>
#include <iostream>

#include "cvars.hpp"

using namespace std;

stringstream readFile(string filename) {
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

	std::string last = "";

	for (int i = 0; i < argc; i++) {
		std::string current = argv[i];

		switch (nextArgumentExpected) {
			case ANY:	
				if (current[0] == '-') {
					nextArgumentExpected = CVAR;
				}

				break;
			case CVAR:
				cvarSet(last.substr(1), current);

				nextArgumentExpected = ANY;
				break;
		}

		last = current;
	}
}

