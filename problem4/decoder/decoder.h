#ifndef DECODER_H
#define DECODER_H

#define RANK 128

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool decoder(const char* inFile, const char* outFile);
pair<unsigned int, string> getData(char* block);

#endif

