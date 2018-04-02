#include <fstream>
#include <sstream>
#include <iostream>

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


