#ifndef  FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define PI 3.14159265

class Gear {
	void fill(int dist1, int dist2, char sb); //рисует окружности с радиусами от dist1 до dist2
	void fill_slot(double an1, double an2); //заполняет сектор от an1 до an2
public:
	Gear(const char* fileName);
	int DPI, width, height;
	int center, r1, r2;
	std::vector<std::string> arr;
	void show_r(double an); //нарисовать радиус по заданному углу
	void show_c(int r); //нарисовать окружность по заданному радиусу
	void show_p(int y, int x); // показать точку по заданным координатам
	void find_slot(); //найти радиусы слотов
	void make_new(const char* fileName); //создать файл со слотами
};

#endif // ! FILE_H
