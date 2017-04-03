#include "arch.h"

using namespace std;

void main(void) {
	setlocale(LC_ALL, "Russian");
	char choose = ' ';
	do {
		cout << "What do you want to do? \n encrypt - e \n decipher - d \n exit - any other symbol" << endl;
		cin >> choose;
		if (choose == 'e') {
			if (!archTo("in.txt")) {
				cout << "I can't read or make file" << endl;
			}
		}
		else if (choose == 'd') {
			if (!archFrom("in.txt")) {
			cout << "I can't read or make file" << endl;
			}
		}
		else break;
	} while (true);
	cout << "Done!" << endl;
	system("pause");
}