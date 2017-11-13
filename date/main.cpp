#include <iostream>
#include "date.h"

using namespace std;

int main(void){
	Date date1;
	cout << date1 << "(" << date1.dayWeek() <<")" << endl;
	date1 += 5;
	cout << "date1 + 5 days = " << date1 << endl;
	date1 = date1 - 5;
	cout << "date1 + 5 days - 5 days = " << date1 << endl;
	cout << endl;

	Date date2("13.11.17");
	cout << date2 << "(" << date2.dayWeek() << ")" << endl;
	date2 += 5;
	cout << "date2 + 5 days = " << date2 << endl;
	date2 = date2 - 5;
	cout << "date2 + 5 days - 5 days = " << date2 << endl;
	cout << endl;

	Date date3("1.12.2017");
	cout << date3 << "(" << date3.dayWeek() << ")"<< endl;
	cout << "How many days between 13.11.2017 and 1.12.2017? " << date3.dist(date2) << endl;
	cout << endl;
	
	system("pause");
	return 1;
}
