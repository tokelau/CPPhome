#include <iostream>
#include <fstream>
#include <map>
#include "decoder.h"

bool decoder(const char* inFile, const char* outFile) {
	ifstream in(inFile);
	ofstream out(outFile);
	if (!in.is_open() || !out.is_open()) return 0;

	in.seekg(0, ios::end);
	unsigned int size = in.tellg();
	in.seekg(0, ios::beg);

	map<unsigned int, string> m;

	unsigned int count = 0;
	char* block = new char[54];
	while (count != size-1) {
		for (int i = 0; !in.eof() && i < 54; i++) {
			block[i] = '/0';
		}
		for (int i = 0; (count != size - 1) && i < 54; i++) {
			block[i] = in.get();
			count++;
		}
		m.insert(getData(block));
		//cout << block << endl;
		//cout << "- " << (int)block[51] << " " <<(int)block[52] <<" "<<(int)block[53]<< endl;
		//cout << "- " << (int)block[51] << " " << (int)block[52] << " " << (int)block[53]<<" : "<<getData(block).first<< " "<< getData(block).second << endl;
	}
	//cout << count << ' ' << size << endl;

	for (map<unsigned int, string>::iterator it = m.begin(); it != m.end(); it++) {
		//cout << (*it).first << " " << (*it).second << endl;
		out << (*it).second.c_str();
	}

	in.close(); out.close();
	return 1;
}

pair<unsigned int, string> getData(char* block) {
	pair<unsigned int, string> temp;
	temp.first = 1;
	temp.second = "1";
	string tempBlock;
	tempBlock.assign(block, 54);
	if (block[53] < RANK) {
		temp.second = tempBlock.substr(0, 53);
		temp.first = (int)tempBlock[53];
		return temp;
	}
	else if (block[52] < RANK) {
		temp.second = tempBlock.substr(0, 52);
		temp.first = RANK + RANK*(int)tempBlock[52] + ((RANK-1) &(int)tempBlock[53]);
		return temp;
	}
	else {
		temp.second = tempBlock.substr(0, 51);
		//cout << (int)tempBlock[51] * RANK*RANK << " + " << ((RANK - 1) & (int)tempBlock[52])*RANK << " + " << ((RANK - 1) & (int)tempBlock[53]) << endl;
		temp.first = RANK*RANK + RANK + (int)tempBlock[51] * RANK*RANK + ((RANK - 1) & (int)tempBlock[52])*RANK + ((RANK - 1) &(int)tempBlock[53]);
		return temp;
	}
}

