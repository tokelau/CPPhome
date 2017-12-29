#include <iostream>
#include <fstream>
#include "decoder.h"

using namespace std;

int main(int argc, const char** argv) {
	if (argc < 3) {
		cout << "Not enough arguments" << endl;
		return 0;
	}
	decoder(argv[1], argv[2]);

	system("pause");
	return 1;
}