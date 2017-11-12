#include "copter.h"
#include <iostream>

using namespace std;

Copter::Copter() {
	energy = 16;
	builds = 0;
	for (int i = 0; i < 16; i++) {
		way[i][0] = way[i][1] = 0;
		direction[i] = FORW;
	}
}

void Copter::findField(Field field, int i, int j, int en, int bd) {
	if (i == -1 || i == 6 || j == -1 || j == 6) return;
	if (en == 0) {
		if (i == 5 && j == 5) {
			if (bd > builds) {
				builds = bd;
				field_ans = field;
			}
			return;
		} else {
			return;
		}
	}
	if (field.field[i][j] != -1) {
		bd += field.field[i][j];
		field.field[i][j] = -1;
	}
	else {
		return;
	}
	en -= 1;
	findField(field, i, j + 1, en, bd);
	findField(field, i - 1, j, en, bd);
	findField(field, i, j - 1, en, bd);
	findField(field, i + 1, j, en, bd);
}

void Copter::findWay(int i, int j, int en) {
	if (i < 0 || j < 0 || i > 5 || j > 5) return;
	if (en < 0) return;
	if (i == 5 && j == 5) {
		way[15 - en][0] = i;
		way[15 - en][1] = j;
		if (field_ans.field[i - 1][j] == -2) direction[15] = FORW;
		if (field_ans.field[i][j - 1] == -2) direction[15] = RIGHT;
		return;
	}
	field_ans.field[i][j] = -2;
	if (field_ans.field[i + 1][j] == -1) {
		way[16 - en][0] = i;
		way[16 - en][1] = j;
		direction[16 - en] = FORW;
		en--;
		findWay(i + 1, j, en);
	} 
	if (field_ans.field[i][j + 1] == -1) {
		way[16 - en][0] = i;
		way[16 - en][1] = j;
		direction[16 - en] = RIGHT;
		en--;
		findWay(i, j + 1, en);
	}
	if (field_ans.field[i - 1][j] == -1) {
		way[16 - en][0] = i;
		way[16 - en][1] = j;
		direction[16 - en] = BACK;
		en--;
		findWay(i - 1, j, en);
	}
	if (field_ans.field[i][j - 1] == -1) {
		way[16 - en][0] = i;
		way[16 - en][1] = j;
		direction[16 - en] = LEFT;
		en--;
		findWay(i, j - 1, en);
	}
}

void Copter::printRes() {
	for (int i = 0; i < 16; i++) {
		cout << (i + 1) << ". (" << way[i][0] << ", " << way[i][1] << "), " << direction[i] << endl;
	}
	return;
}