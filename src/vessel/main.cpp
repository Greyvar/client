#include <sys/stat.h>
#include <iostream>

using namespace std;

int mainGreyvarCore(int argc, char* argv[]);

bool directoryExists(const char* path) {
	bool exists = false;
	struct stat statResult;

	if (path != NULL) {
		if (stat(path, &statResult) == 0 && S_ISDIR(statResult.st_mode)) {
			exists = true;
		}
	}

	return exists;
}

int main(int argc, char* argv[]) {
	cout << "Greyvar (vessel) " << endl << "----------------" << endl;

	if (!directoryExists("res")) {
		cout << "res directory not found." << endl;
	} else {
		cout << "Vessel checks complete. Starting the core..." << endl << endl;
		mainGreyvarCore(argc, argv);
	}

	return 0;
}
