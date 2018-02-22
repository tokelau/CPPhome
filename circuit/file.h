#ifndef _FILE_H
#define _FiLE_H

#include "circuit.h"

//чтение файла
bool readFile(const char* fileName, File* arr);
//запись массива с контурами
bool writeFile(const char* fileName, const File* arr);
//запись координат контура
bool writeCoordinates(const char* fileName, const int line, const int column);

#endif
