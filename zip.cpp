#include <iostream>
#include <fstream>

using namespace std;

void toZip(const char* inFile, const char* outFile) {
	ifstream in(inFile);
	ofstream out(outFile);
	if (!in.is_open() || !out.is_open()) return;
	char ch, ch2, done, t;
	done = 0;
	do {
		ch = in.get();
		cout << (int)ch << ' ';
		for (char i = 0; i < 7; i++) {
			ch2 = in.get();
			//cout << ch2;
			if (in.eof()) {
				ch2 = 0;
				done = 1;
			}
			ch2 = ch2 & 127;
			ch2 = ch2 | ((ch << (i + 1)) & 128);
			//cout << (int)ch2 << ' ';
			out.put((char)ch2);
		}
	} while (!in.eof() && !done);
	cout << '\n';
	in.close();
	out.close();
}

void fromZip(const char* inFile, const char* outFile) {
	ifstream in(inFile);
	ofstream out(outFile);
	if (!in.is_open() || !out.is_open()) return;
	char ch, ch2, done, t;
	char s[7] = { 0, 0, 0, 0, 0, 0, 0 };
	done = 0;
	do {
		ch = 0;
		for (t = 0; t < 7; t++) {
			ch2 = in.get();
			if (in.eof()) break;
			s[t] = ch2 & 127;
			ch2 = ch2 & 128;
			if (ch2 != 0) ch2 = 1;
			ch2 = ch2 << (6 - t);
			ch = ch | ch2;
		}
		if (!in.eof()){
			out.put((char) ch);
			cout << (char)ch << ' ';
			for (t = 0; t < 7; t++) {
				if((int)s[t] != 0) out.put((char) s[t]);
				cout << (int)s[t]<<' ';
			}
		}
	} while (!done && !in.eof());
	in.close();
	out.close();
}

int main(int argc, char** argv) {
	if (argc < 3) {
		cout << "Not enough arguments" << endl;
		return -1;
	} 
	toZip(argv[1], argv[2]);
	fromZip(argv[1], argv[2]);
	system("pause");
	return 1;
}
