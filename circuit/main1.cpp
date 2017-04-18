#include "file.h"
#include "circuit.h"
#include <iostream>
//#include <fstream>

using namespace std;

int main() {
	File arr;
	if (!readFile("res-2.txt", &arr)) {
		cout << "I can't read file" << endl;
		return -1;
	}
	findCircuit(&arr, 0, 0);
	if (!writeFile("out.txt", &arr)) {
		cout << "I can't write file" << endl;
		return -1;
	}
	cout << "Done!" << endl;
	system("pause");
	return 1;
}