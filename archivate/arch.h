#ifndef _ARCH_H
#define _ARCH_H

#include <iostream>
#include <locale.h>
#include <fstream>

using namespace std;

bool archTo(const char* filename);
bool archFrom(const char* filename);
bool write(const register unsigned char* wr);

#endif