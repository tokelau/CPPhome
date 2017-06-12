#include <fstream>
#include <iostream>

using namespace std;

void replacement(const char* fileName) {
	ifstream in(fileName);
	ofstream out("out.txt");
	if (!in || !out) {
		cout << "Can't read or write file." << endl;
		return;
	}
	char ch;
	int i = 0, count = 0;
	do {
		ch = in.get();
		if (ch == '(') count++;
	} while (!in.eof());
	in.clear();
	in.seekg(0, ios::beg);
	do {
		ch = in.get();
		if ((int)ch == -1) {
			break;
		}
		if (ch == '(') {
			if (count > 2) {
				ch = '{';
			}
			else if (count == 2) {
				ch = '[';
			}
			count--;
		}
		if (ch == ')') {
			if (count == 1) {
				ch = ']';
			}
			else if (count >= 2) {
				ch = '}';
			}
			count++;
		}
		out.put(ch);
	} while (!in.eof());
}

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "Not enough arguments" << endl;
		return -1;
	}
	replacement(argv[1]);
	system("pause");
	return 1;
}