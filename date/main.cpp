#include <iostream>
#include "date.h"

using namespace std;

int main(void){
	Date data("10.11.2017");
	Date d1("04.05.16");
	data = d1 + 21;
	cout<<data;
	system("pause");
	return 1;
}