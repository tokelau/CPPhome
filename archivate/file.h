#ifndef _FILE_H
#define _FiLE_H

#include "circuit.h"

//читает массив из файла
bool readFile(const char* fileName, File* arr);
//записывает массив в выходной файл
bool writeFile(const char* fileName, const File* arr);
//записывает координаты во второй выходной файл
bool writeCoordinates(const char* fileName, const int line, const int column);

#endif
