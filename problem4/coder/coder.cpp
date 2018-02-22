#include <iostream>
#include <fstream>
#include "coder.h"

using namespace std;

int blockSize = 53; //èçíà÷àëüíûé ðàçìåð áëîêà
int idSize = 1;
unsigned char id = 0;
unsigned char id_1 = 0;
unsigned char id_2 = 0;

/*кодируем первый байт*/
bool firstLevel(const char* infile, const char* outFile) {
	ifstream in(infile);
	ofstream out(outFile, ios::app);
	if (!in.is_open() || !out.is_open()) return 0;

	char* block = new char[blockSize + 1];

	/*çàìåíèòü íà 128*/
	while (!in.eof() && id != RANK) {
		for (int i = 0; i < 54; i++) {
			block[i] = 0;
		}
		in.read(block, blockSize);
		block[53] = id++;
		out.write(block, 54);
		//cout << in.tellg() << endl;
	}
	
	/*одного байта нам не хватило, берем второй*/
	if (!in.eof()) {
		blockSize--; //52
		secondLevel(in, out);
	}
	
	in.close(); out.close();
	return 1;
}

/*кодируем второй байт*/
void secondLevel(ifstream& in, ofstream& out) {
	char* block = new char[blockSize + 2]; //54
	for (int i = 0; i < 54; i++) {
		block[i] = 0;
	}
	
	/*пока первый бит этого байта меньше единицы*/
	for (id_1; !in.eof() && id_1 < RANK;) {
		while (!in.eof() && id != RANK*2) {
			for (int i = 0; i < 54; i++) {
				block[i] = 0;
			}
			in.read(block, 52);
			//cout << block << endl;
			block[52] = id_1;
			block[53] = id;
			if (!in.eof()) {
				id++;
			}
			out.write(block, 54);
		}
		if (!in.eof()) {
			id_1++;
			id = RANK;
		}
	}
	/*второго байта нам не хватило, берем третий*/
	if (!in.eof()) {
		id_1 = RANK;
		id = RANK;
		blockSize--; //51
		thirdLevel(in, out);
	} 
	in.close(); out.close();
	//cout << "It's okay" << endl;
}

/*кодируем третий байт*/
void thirdLevel(ifstream& in, ofstream& out) {
	char* block = new char[blockSize + 3]; //54
	for (int i = 0; i < 54; i++) {
		block[i] = 0;
	}

	for (id_2; !in.eof() && id_2 != RANK;) {
		for (id_1; !in.eof() && id_1 != RANK * 2;) {
			while (!in.eof() && id != RANK * 2) {
				for (int i = 0; i < 54; i++) {
					block[i] = 0;
				}
				in.read(block, 51);
				cout << (int)block[0] << endl;
				block[51] = id_2;
				block[52] = id_1;
				block[53] = id;
				if (!in.eof()) {
					id++;
				}
				out.write(block, 54);
			}
			if (!in.eof()) {
				id_1++;
				id = RANK;
			}
		}
		if (!in.eof()) {
			id_2++;
			id_1 = RANK;
			id = RANK;
		}
	}
	//out << '\0';
	in.close(); out.close();
	cout << "It's okay" << endl;
}
