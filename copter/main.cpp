#include <iostream>
#include "field.h"
#include "copter.h"

using namespace std;

int main(void){
	Field field;
	Copter copt;
	copt.findField(field, 0, 0, copt.energy, 0);
	copt.field_ans.field_out();
	copt.findWay(0, 0, 16);
	copt.printRes();
	system("pause");
	return 1;
}