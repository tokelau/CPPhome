#ifndef _FILE_H
#define _FiLE_H

#include "circuit.h"

//������ ������ �� �����
bool readFile(const char* fileName, File* arr);
//���������� ������ � �������� ����
bool writeFile(const char* fileName, const File* arr);
//���������� ���������� �� ������ �������� ����
bool writeCoordinates(const char* fileName, const int line, const int column);

#endif
