#include <iostream>
#include "rational.h"

using namespace std;

int main(void) {
	setlocale(LC_ALL, "rus");
	Rational A(2, 3);
	Rational B(5, 3);
	cout << "2/3" << " + 5/3" << " = " << A + B << endl;
	cout << "2/3" << " - 5/3" << " = " << A - B << endl;
	cout << "2/3" << " * 5/3" << " = " << A * B << endl;
	cout << "2/3" << " / 5/3" << " = " << A / B << endl;
	cout << "2/3 � ������� 3 = " << A.power(A, 3) << endl;
	cout << "���������� ������ �� 8/27 = " << A.radical(Rational(8,27), 2) << endl;
	system("pause");
	return 1;
}