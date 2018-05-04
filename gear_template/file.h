#ifndef  FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define PI 3.14159265

class Gear {
	void fill(int dist1, int dist2, char sb); //������ ���������� � ��������� �� dist1 �� dist2
	void fill_slot(double an1, double an2); //��������� ������ �� an1 �� an2
public:
	Gear(const char* fileName);
	int DPI, width, height;
	int center, r1, r2;
	std::vector<std::string> arr;
	void show_r(double an); //���������� ������ �� ��������� ����
	void show_c(int r); //���������� ���������� �� ��������� �������
	void show_p(int y, int x); // �������� ����� �� �������� �����������
	void find_slot(); //����� ������� ������
	void make_new(const char* fileName); //������� ���� �� �������
};

#endif // ! FILE_H
