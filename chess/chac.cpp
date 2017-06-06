#include <iostream>
#include <fstream>

using namespace std;
const int COFF = 10000; 

bool checkNumber(ifstream& in, int* wcount, int* bcount); //������������ ���-�� ����� ������ � ������� �����
int* readCoordinates(ifstream& in, int* number); //��������� ���������� � �������� �����
bool writeCoordinates(int* number1, int* number2); // ���������� �����
int getVert(int *number); //�������� ������������ ���������
int getHoris(int *number); // �������� �������������� ����������
bool checkLines(int* checkFigure, int* checkArr, int* Arr); //���� ������, ������� �������� �� ��������� � �����������
bool checkDiagonals(int* checkFigure, int* checkArr, int* Arr); //���� ������, ������� �������� �� ����������
bool checkOneMove(int* checkFigure, int* Arr, char flag); //������� ��� ���� ����� � ������
bool checkNight(int* checkFigure, int* Arr); //������ ��� ����

bool checkNumber(ifstream& in, int* wcount, int* bcount) {
	if (!in.is_open()) {
		return 0;
	}
	char ch;
	while(!in.eof()){
		in >> ch; 
		if (ch == ':' && *wcount == -1) {
			in >> ch;
			*wcount = ch - '1' + 1;
		}
		else if (ch == ':' && *bcount == -1) {
			in >> ch;
			*bcount = ch - '1' + 1;
			break;
		}
	}
	in.seekg(0); //���������� ������ �� ������ ������ �����
	return 1;
}
int* readCoordinates(ifstream& in, int* number) {
	if (!in.is_open()) {
		return 0;
	}
	int* arr = new int[*number];
	for (int i = 0; i < *number; i++) {
		arr[i] = 0; 
	}
	int n = 0;
	char ch;
	int coff = COFF;
	while (!in.eof()) {
		in >> ch;
		if (ch == ':') {
			in >> ch;
			while(n != *number-1) { 
				in >> ch; //������� ������ ������ ����� � �������� ������ � ������
				arr[n] += (int)ch * coff; //������� ������ ������ (�������� ������)
				coff /= 100;
				in >> ch;
				arr[n] += (int)ch * coff;//������ ������ - �������������� ���������� ������
				coff /= 100;
				in >> ch;
				arr[n] += (int)ch * coff; //������ - ������������ ����������
				coff = COFF;
				n++;
			}
			/*� ����� ���������� 6-��������� (��� ����� - 7-���������) �����, ������� �������� ��� 
			��� ������ � �� ����������*/
			return arr;
		}
	}
}
bool writeCoordinates(int* number1, int* number2) { 
	ofstream out("out.txt", ios_base::in | ios_base::app); //�� ����� ������� ������� ����� ������ �������, �� � ���� ���� �� ���������, � ���������� ������
	if (!out.is_open()) {
		cout << "Can't make output file" << endl;
		return 0;
	}
	/*������ ��� ����� ������������ ������ �������*/
	char ch[3];
	ch[0] = *number1 / COFF;
	ch[1] = (*number1 / 100) % 100;
	ch[2] = *number1 % 100;
	out << ch[0] << ch[1] << ch[2] << "-"<<">";
	ch[0] = *number2 / COFF;
	ch[1] = (*number2 / 100) % 100;
	ch[2] = *number2 % 100;
	out << ch[0] << ch[1] << ch[2] << endl;
	return 1;
}
int getVert(int *number) {
	return *number % 10000 / 100; 
}
int getHoris(int *number) {
	return *number % 100;
}
bool checkLines(int* checkFigure, int* checkArr, int* Arr) {
	/*� ����� ��� ����� ���� ������ ����������� ����, ���� ������ - ����������� ������, ������� ����� ���� �� ������� � ������ �����,
	���� ��������� 4 �����, ������ ������������� ������ ������� ����� ���� ��� �������, �� �������� ����� ���� ������, �����
	�� ���� ��������� �� ��������� (Vdistance1) � ����������� (Hdistance1) ������ �� ������� ������� � ���������� ���������� �� ���,
	�� ������ ����� �� ������ ��� �� �� �����, �� ��� ������� �����-����������� � ��� ��������� �� ������ ���������� 
	�� ����������� (Vdistance2)	� ��������� (Hdistance2) ��� ���, �� � ���������� ��������������� � ������-����������,
	� ������� � ��������� ����� ������ ������������ �������� ��� ����� ������ ����� ����*/
	int Vdistance1 = 8; 
	int Vdistance2 = 8;
	int Hdistance1 = 8;
	int Hdistance2 = 8;
	int Vfigure1 = 0;
	int Vfigure2 = 0;
	int Hfigure1 = 0;
	int Hfigure2 = 0;
		for (int j = 0; checkArr[j] != 0; j++) {
			if ((getHoris(&checkArr[j]) > getHoris(checkFigure)) && (getHoris(&checkArr[j]) - getHoris(checkFigure) < Vdistance1) && (getVert(&checkArr[j]) == getVert(checkFigure))) {
				Vdistance1 = getHoris(&checkArr[j]) - getHoris(checkFigure);
			}
			if ((getVert(&checkArr[j]) > getVert(checkFigure)) && (getVert(&checkArr[j]) - getVert(checkFigure) < Hdistance1) && (getHoris(&checkArr[j]) == getHoris(checkFigure))) {
				Hdistance1 = getVert(&checkArr[j]) - getVert(checkFigure);
			}
		}
		for (int j = 0; Arr[j] != 0; j++) {
			if ((getHoris(&Arr[j]) > getHoris(checkFigure)) && (getHoris(&Arr[j]) - getHoris(checkFigure) < Vdistance2) && (getVert(&Arr[j]) == getVert(checkFigure))) {
				Vdistance2 = getHoris(&Arr[j]) - getHoris(checkFigure);
				//cout << distance2 << endl;
				Vfigure1 = *checkFigure;
				Vfigure2 = Arr[j];
			}
			if ((getVert(&Arr[j]) > getVert(checkFigure)) && (getVert(&Arr[j]) - getVert(checkFigure) < Hdistance2) && (getHoris(&Arr[j]) == getHoris(checkFigure))) {
				Hdistance2 = getVert(&Arr[j]) - getVert(checkFigure);
				Hfigure1 = *checkFigure;
				Hfigure2 = Arr[j];
			}
		}
	if (Vdistance2 < Vdistance1) { //���������� � ����, ���� ���������� �� ���������� �����, ��� �� ����� ������
		if (!writeCoordinates(&Vfigure1, &Vfigure2)) {
			return 0;
		}
	}
	if (Hdistance2 < Hdistance1) {
		if (!writeCoordinates(&Hfigure1, &Hfigure2)) {
			return 0;
		}
	}
	Vdistance1 = 8;
	Vdistance2 = 8;
	Hdistance1 = 8;
	Hdistance2 = 8;
		for (int j = 0; checkArr[j] != 0; j++) {
			if ((getHoris(&checkArr[j]) < getHoris(checkFigure)) && (getHoris(checkFigure) - getHoris(&checkArr[j]) < Vdistance1) && (getVert(&checkArr[j]) == getVert(checkFigure))) {
				Vdistance1 = getHoris(checkFigure) - getHoris(&checkArr[j]);
			}
			if ((getVert(&checkArr[j]) < getVert(checkFigure)) && (getVert(checkFigure) - getVert(&checkArr[j]) < Hdistance1) && (getHoris(&checkArr[j]) == getHoris(checkFigure))) {
				Hdistance1 = getVert(&checkArr[j]) - getVert(checkFigure);
			}
		}
		for (int j = 0; Arr[j] != 0; j++) {
			if ((getHoris(&Arr[j]) < getHoris(checkFigure)) && (getHoris(checkFigure) - getHoris(&Arr[j]) < Vdistance1) && (getVert(&Arr[j]) == getVert(checkFigure))) {
				Vdistance2 = getHoris(checkFigure) - getHoris(&Arr[j]);
				Vfigure1 = *checkFigure;
				Vfigure2 = Arr[j];
			}
			if ((getVert(&Arr[j]) < getVert(checkFigure)) && (getVert(checkFigure) - getVert(&Arr[j]) < Hdistance1) && (getHoris(&Arr[j]) == getHoris(checkFigure))) {
				Hdistance2 = getVert(checkFigure) - getVert(&Arr[j]);
				Hfigure1 = *checkFigure;
				Hfigure2 = Arr[j];
			}
		}
	if (Vdistance2 < Vdistance1) {
		if (!writeCoordinates(&Vfigure1, &Vfigure2)) {
			return 0;
		}
	}
	if (Hdistance2 < Hdistance1) {
		if (!writeCoordinates(&Hfigure1, &Hfigure2)) {
			return 0;
		}
	}
	return 1;
}
bool checkDiagonals(int* checkFigure, int* checkArr, int* Arr) {
	/*� ����� ������� ������� �������, �� ���� ������� �� ������ � ����� �����*/
	int Tdistance1 = 8;
	int Tdistance2 = 8;
	int Bdistance1 = 8;
	int Bdistance2 = 8;
	int Tfigure1 = 0;
	int Tfigure2 = 0;
	int Bfigure1 = 0;
	int Bfigure2 = 0;
	for (int j = 0; checkArr[j] != 0; j++) {
		if ((getVert(&checkArr[j]) - getVert(checkFigure) == getHoris(&checkArr[j]) - getHoris(checkFigure)) && (getVert(&checkArr[j]) > getVert(checkFigure))) {
			if (getHoris(&checkArr[j]) - getHoris(checkFigure) < Tdistance1) {
				Tdistance1 = getHoris(&checkArr[j]) - getHoris(checkFigure);
			}
		}
		if ((getVert(&checkArr[j]) - getVert(checkFigure) == -1 * (getHoris(&checkArr[j]) - getHoris(checkFigure))) && (getVert(&checkArr[j]) > getVert(checkFigure))) {
			if (getHoris(&checkArr[j]) - getHoris(checkFigure) < Bdistance1) {
				Bdistance1 = getHoris(&checkArr[j]) - getHoris(checkFigure);
			}
		}
	}
	for (int j = 0; Arr[j] != 0; j++) {
		if ((getVert(&Arr[j]) - getVert(checkFigure) == getHoris(&Arr[j]) - getHoris(checkFigure)) && (getVert(&Arr[j]) > getVert(checkFigure))) {
			if (getHoris(&Arr[j]) - getHoris(checkFigure) < Tdistance2) {
				Tdistance2 = getHoris(&Arr[j]) - getHoris(checkFigure);
				Tfigure1 = *checkFigure;
				Tfigure2 = Arr[j];
			}
		}
		if ((getVert(&Arr[j]) - getVert(checkFigure) == -1 * (getHoris(&Arr[j]) - getHoris(checkFigure))) && (getVert(&Arr[j]) > getVert(checkFigure))) {
			if (getHoris(&Arr[j]) - getHoris(checkFigure) < Bdistance2) {
				Bdistance2 = getHoris(&Arr[j]) - getHoris(checkFigure);
				cout << 1 << endl;
				Bfigure1 = *checkFigure;
				Bfigure2 = Arr[j];
			}
		}
	}
	if (Tdistance2 < Tdistance1) {
		if (!writeCoordinates(&Tfigure1, &Tfigure2)) {
			return 0;
		}
	}
	if (Bdistance2 < Bdistance1) {
		if (!writeCoordinates(&Bfigure1, &Bfigure2)) {
			return 0;
		}
	}
	Tdistance1 = 8;
	Tdistance2 = 8;
	Bdistance1 = 8;
	Bdistance2 = 8;
	for (int j = 0; checkArr[j] != 0; j++) {
		if ((getVert(checkFigure) - getVert(&checkArr[j]) == getHoris(checkFigure) - getHoris(&checkArr[j])) && (getVert(&checkArr[j]) < getVert(checkFigure))) {
			if (getHoris(checkFigure) - getHoris(&checkArr[j]) < Tdistance1) {
				Tdistance1 = getHoris(checkFigure) - getHoris(&checkArr[j]);
			}
		}
		if ((getVert(checkFigure) - getVert(&checkArr[j]) == -1 * (getHoris(checkFigure) - getHoris(&checkArr[j]))) && (getVert(&checkArr[j]) < getVert(checkFigure))) {
			if (getHoris(checkFigure) - getHoris(&checkArr[j]) < Bdistance1) {
				Bdistance1 = getHoris(checkFigure) - getHoris(&checkArr[j]);
			}
		}
	}
	for (int j = 0; Arr[j] != 0; j++) {
		if ((getVert(checkFigure) - getVert(&Arr[j]) == getHoris(checkFigure) - getHoris(&Arr[j])) && (getVert(&Arr[j]) < getVert(checkFigure))) {
			if (getHoris(checkFigure) - getHoris(&Arr[j]) < Tdistance2) {
				Tdistance2 = getHoris(checkFigure) - getHoris(&Arr[j]);
				Tfigure1 = *checkFigure;
				Tfigure2 = Arr[j];
			}
		}
		if ((getVert(checkFigure) - getVert(&Arr[j]) == -1 * (getHoris(checkFigure) - getHoris(&Arr[j]))) && (getVert(&Arr[j]) < getVert(checkFigure))) {
			if (getHoris(checkFigure) - getHoris(&Arr[j]) < Bdistance2) {
				Bdistance2 = getHoris(checkFigure) - getHoris(&Arr[j]);
				//cout << 1 << endl;
				Bfigure1 = *checkFigure;
				Bfigure2 = Arr[j];
			}
		}
	}
	if (Tdistance2 < Tdistance1) {
		if (!writeCoordinates(&Tfigure1, &Tfigure2)) {
			return 0;
		}
	}
	if (Bdistance2 < Bdistance1) {
		if (!writeCoordinates(&Bfigure1, &Bfigure2)) {
			return 0;
		}
	}
	//int Vert = *checkFigure % 10000 / 100;
	//int Horis = (*checkFigure % 100);
	//for (int i = 0; i < 8; i++) {
	//	if ((checkArr[i] % 10000 / 100) - Vert == checkArr[i] % 100 - Horis && checkArr[i] % 100 > Horis) {
	//		//cout << 1;
	//		break;
	//	}
	//	else if ((Arr[i] % 10000 / 100) - Vert == Arr[i] % 100 - Horis && Arr[i]%100 > Horis ){
	//		if (!writeCoordinates(checkFigure, &Arr[i])) {
	//			return 0;
	//		}
	//		//cout << 8;
	//	}
	//}
	//for (int i = 8; i > 0; i--) {
	//	if ((Vert - (checkArr[i] % 10000 / 100))  == (checkArr[i] % 100 - Horis) && checkArr[i] % 100 < Horis) {
	//		break;
	//	}
	//	else if (Vert - (Arr[i] % 10000 / 100) == Arr[i] % 100 - Horis && Arr[i] % 100 < Horis) {
	//		if (!writeCoordinates(checkFigure, &Arr[i])) {
	//			return 0;
	//		}
	//	}
	//}
	return 1;
}
bool checkOneMove(int* checkFigure, int* Arr, char flag) {
	//���������� flag ����� ��� ����, ����� �������� ������ �� �����
	for (int j = 0; Arr[j] != 0; j++) {
		//������������� ����������� �� ��������� ����� ������ � ����� �� ���� ������
		if ((getHoris(checkFigure) + 1 == getHoris(&Arr[j])) && ((getVert(checkFigure) + 1 == getVert(&Arr[j])) || (getVert(checkFigure) - 1 == getVert(&Arr[j])))) {
			if (!writeCoordinates(checkFigure, &Arr[j])) {
				return 0;
			}
		}
		if (flag == 'K') {
			//������������� ����������� �� ��������� ���� ������ � ����� �� ���� ������
			if ((getHoris(checkFigure) - 1 == getHoris(&Arr[j])) && ((getVert(checkFigure) + 1 == getVert(&Arr[j])) || (getVert(checkFigure) - 1 == getVert(&Arr[j])))) {
				if (!writeCoordinates(checkFigure, &Arr[j])) {
					return 0;
				}
			}
			//������������� ����������� �� ����������� ������ � ����� �� ���� ������
			if (getHoris(checkFigure) == getHoris(&Arr[j]) && ((getVert(checkFigure) + 1 == getVert(&Arr[j])) || (getVert(checkFigure) - 1 == getVert(&Arr[j])))) {
				if (!writeCoordinates(checkFigure, &Arr[j])) {
					return 0;
				}
			}
			//������������� ����������� �� ��������� ������ � ����� �� ���� ������
			if (getVert(checkFigure) == getVert(&Arr[j]) && (getHoris(checkFigure) + 1 == getHoris(&Arr[j]) || getHoris(checkFigure) - 1 == getHoris(&Arr[j]))) {
				if (!writeCoordinates(checkFigure, &Arr[j])) {
					return 0;
				}
			}
		}
	}
	return 1;
}
bool checkNight(int* checkFigure, int* Arr) {
	for (int j = 0; Arr[j] != 0; j++) {
		//������������� ��� ���� �� ���� ������ ������ � �� ��� ����� � ����
		if (getVert(checkFigure) + 1 == getVert(&Arr[j]) && ((getHoris(checkFigure) + 2 == getHoris(&Arr[j])) || (getHoris(checkFigure) - 2 == getHoris(&Arr[j])))) {
			if (!writeCoordinates(checkFigure, &Arr[j])) {
				return 0;
			}
		}
		//������������� ��� ���� �� ���� ������ ����� � �� ��� ����� � ����
		if (getVert(checkFigure) - 1 == getVert(&Arr[j]) && ((getHoris(checkFigure) + 2 == getHoris(&Arr[j])) || (getHoris(checkFigure) - 2 == getHoris(&Arr[j])))) {
			if (!writeCoordinates(checkFigure, &Arr[j])) {
				return 0;
			}
		}
		//������������� ��� ���� �� ��� ������ ������ � �� ���� ����� � ����
		if (getVert(checkFigure) + 2 == getVert(&Arr[j]) && ((getHoris(checkFigure) + 1 == getHoris(&Arr[j])) || (getHoris(checkFigure) - 1 == getHoris(&Arr[j])))) {
			if (!writeCoordinates(checkFigure, &Arr[j])) {
				return 0;
			}
		}
		//������������� ��� ���� �� ��� ������ ����� � �� ���� ����� � ����
		if (getVert(checkFigure) - 2 == getVert(&Arr[j]) && ((getHoris(checkFigure) + 1 == getHoris(&Arr[j])) || (getHoris(checkFigure) - 1 == getHoris(&Arr[j])))) {
			if (!writeCoordinates(checkFigure, &Arr[j])) {
				return 0;
			}
		} 
	}
	return 1;
}

//	/*��������, �� ����� �� ������ �� ����� ������, � ��� � �� ������, ��� ��� ����������� ����� ����� �������*/
	//	if (getVert(checkFigure) == getVert(&Arr[i]) && getHoris(checkFigure) == getHoris(&Arr[i])) {
	//		cout << "Two figures occupy the same cage!" << endl;
	//		return 0;
	//	}
	//	if (getVert(checkFigure) == getVert(&checkArr[i]) && getHoris(checkFigure) == getHoris(&checkArr[i])) {
	//		cout << "Two figures occupy the same cage!" << endl;
	//		return 0;
	//	}
	//}
bool isThreaten(int* checkArr, int* Arr) {
	int n = 0;
	while (checkArr[n] != 0) { 
		if ((char)(checkArr[n] / COFF) == 'K') {
			if (!checkOneMove(&checkArr[n], Arr, 'K')) {
				return 0;
			}
		}
		if ((char)(checkArr[n] / COFF) == 'Q') {
			if (!checkLines(&checkArr[n], checkArr, Arr) || !checkDiagonals(&checkArr[n], checkArr, Arr)) {
				return 0;
			}
		}
		if ((char)(checkArr[n] / COFF) == 'R') {
			if (!checkLines(&checkArr[n], checkArr, Arr)) {
				return 0;
			}
		}
		if ((char)(checkArr[n] / COFF) == 'N') {
			if (!checkNight(&checkArr[n], Arr)) {
				return 0;
			}
		}
		if ((char)(checkArr[n] / COFF) == 'B') {
			if (!checkDiagonals(&checkArr[n], checkArr, Arr)) {
				return 0;
			}
		}
		if ((char)(checkArr[n] / COFF) == 'p') {
			if (!checkOneMove(&checkArr[n], Arr, 'p')) {
				return 0;
			}
		}
		n++;
	}
	return 1;
}

bool main(void) {
	int wcount = -1, bcount = -1;
	ifstream in("in.txt");
	if (!checkNumber(in, &wcount, &bcount)) {
		cout << "Failed to read input file" << endl;
		return 0;
	}
	int* warr = new int[wcount++]; //����������� ������� �� 1 ������, ��� ���-�� �����,���������� �� ����� �������� 0
	int* barr = new int[bcount++]; // � ����� ������� ����� �����, ��� ����� � ���������� ��������
	/*if (readCoordinates(in, &wcount) == &wcount) { //� ��-�� ����� ������� � ���� ������-�� �������� ��� ���������
		cout << "Filed to read possitions"<<endl;
		return 0;
	}*/
	warr = readCoordinates(in, &wcount);
	/*if (readCoordinates(in, &bcount) == &bcount) { 
		cout << "Filed to read possitions" << endl;
		return 0;
	}*/
	barr = readCoordinates(in, &bcount);
	if (!isThreaten(warr, barr)) { 
		cout << "Can't check threat";
		return 0;
	}
	if (!isThreaten(barr, warr)) {
		cout << "Can't check threat";
		return 0;
	}
	cout << "Did it!" << endl;
	system("pause");
}
