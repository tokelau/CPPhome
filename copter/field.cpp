#include <iostream>
#include "field.h"

using namespace std;

Field::Field(){
	int fieldF[6][6] = {{0, 0, 3, 0, 9, 6 }, 
						{0, 6, 0, 2, 0, 0},
						{0, 0, 3, 0, 0, 5 },
						{7, 0, 0, 4, 0, 0},
						{3, 0, 4, 0, 1, 0 },
						{0, 10, 0, 1, 0, -1 }};
	for(int i = 0; i<6; i++){
		for(int j =0; j<6; j++){
			field[i][j] = fieldF[i][j];
		}
	}
}

void Field::field_out() {
	for (int ii = 5; ii >=0; ii--) {
		for (int jj = 0; jj < 6; jj++) {
			cout << (*this).field[ii][jj] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	return;
}

Field& Field::operator = (const Field& f) {
	for (int ii = 5; ii >= 0; ii--) {
		for (int jj = 0; jj < 6; jj++) {
			field[ii][jj] = f.field[ii][jj];
		}
	}
	return *this;
}