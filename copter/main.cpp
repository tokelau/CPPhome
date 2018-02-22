#include <iostream>
#include "field.h"
#include "copter.h"

using namespace std;

int main(void){
	Field field;
	Copter copt;
	//ищет вариант поля, подходящий под условие
	copt.findField(field, 0, 0, copt.energy, 0);
	//выводит в консоль поле с ответом
	copt.field_ans.field_out();
	//ищет путь и направления поворота
	copt.findWay(0, 0, 16);
	//выводит окончательный результат
	copt.printRes();
	system("pause");
	return 1;
}
