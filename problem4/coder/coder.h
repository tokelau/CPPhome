#ifndef CODER_H
#define CODER_H

#define RANK 128

#include <iostream>
#include <fstream>

using namespace std;


bool firstLevel(const char* infile, const char* outFile);
void secondLevel(ifstream& in, ofstream& out);
void thirdLevel(ifstream& in, ofstream& out);

#endif