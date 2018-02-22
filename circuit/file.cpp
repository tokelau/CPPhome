#include <iostream>
#include <fstream>
#include "circuit.h"

using namespace std;

bool readFile(const char* fileName, File* arr) {
	ifstream in(fileName);
	if (!in.is_open()) return 0;
	in >> arr->px; 
	in >> arr->column; //сохраняем в структуру количество столбцов
	in >> arr->row; //сохраняем в структуру количество строк
	register char ch;
	char* p1;
	/* копируем в струтуру входной файл */
	arr->In = new char*[arr->row]; 
	for (int i = 0; i < arr->row; i++) {
		p1 = new char[arr->column];
		for (int j = 0; j < arr->column; j++) {
			in >> ch;
			if (ch == '1') {
				p1[j] = '1';
			}
			else if (ch == '0') {
				p1[j] = '0';
			}
		}
		arr->In[i] = p1;
	}
	cout << "The file has been successfully read..." << endl;
	return 1;
}

bool writeFile(const char* fileName, const File* arr) {
	ofstream out(fileName);
	if (!out.is_open()) return 0;
	out << arr->px << ' ' << arr->row << ' ' << arr->column << '\n';
	for (int i = 0; i < arr->row; i++) {
		for (int j = 0; j < arr->column; j++) {
			if (arr->In[i][j] == '2') {
				out << '1';
			}
			else {
				out << '0';
			}
		}
		out << '\n';
	}
	cout << "File successfully recorded..." << endl;
	return 1;
}

bool writeCoordinates(const char* fileName, const int line, const int column) {
	ofstream out(fileName, ios_base::app);
	if (!out.is_open()) return 0;
	out << line << ' ' << column << ";" << "\n";
	return 1;
}
