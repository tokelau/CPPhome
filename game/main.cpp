#include <iostream>
#include "game.h"

using namespace std;

int main(void) {
	setlocale(LC_ALL, "Russian");
	Field field(true);

	while (!field.isOver())
	{
		field.print();
		cout<<"����� "<<
		(field.isRedTurnNow() ? "�������" : "������")<<" �����, ������� ��� (1-7)"<<endl;
		int column; 
		cin>>column;
		field.makeTurn(column);
		system("cls");
	}
	field.printResult();

	system("pause");
	return 1;
}