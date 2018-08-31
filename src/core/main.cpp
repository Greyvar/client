#include <boleas.hpp>

#include <cstdlib>
#include <ctime>
#include <iostream>

using std::cout;
using std::endl;

int mainGreyvarCore(int argc, char* argv[]) {
	cout << "Greyvar (core) " << endl << "--------------" << endl;

	boleasSayHello();

	boleasStartEngine();

	cout << "Everything has quit. Bye! " << endl;

	return 0;
}
