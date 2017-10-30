#include <iostream>
#include "room.h"

using namespace std;

int main(void){
	Room myRoom(2, -2.0, 3.0, 4.0);
	try{
		cout<<myRoom.CalcRoom()<<endl;
	}
	catch (...){
		cout << "There is some error. " << endl;
	}
	system("pause");
	return 1;
}