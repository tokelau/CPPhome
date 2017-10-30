#include <iostream>
#include "game.h"

using namespace std;

Field::Field(bool isRedFirst) {
	clear(isRedFirst);
}

void Field::clear(bool isRedFirst) {
	isRedTurn = isRedFirst;
	winner = EMPTY;
	for(int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			cells[i][j] = EMPTY;
		}
	}
}

bool Field::makeTurn(int column) {
	if (winner != EMPTY || column < 1 || column > 7) return false;
	int i = column - 1;
	for (int j = 0; j < 6; j++) {
		if (cells[i][j] == EMPTY) {
			cells[i][j] = isRedTurn ? RED : YELLOW;
			checkWinner();
			isRedTurn = !isRedTurn;
			return true;
		}
	}
	return false;
}

void Field::checkWinner() {
	const int di[] = { 1, 0, 1, 1 }; 
	const int dj[] = { 0, 1, -1, 1 };
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			Cell start = cells[i][j];
			if (start == EMPTY) continue;
			for (int dir = 0; dir < 4; dir++) {
				int lenght = 0, iline = i, jline = j;
				while (++lenght < 4) {
					iline += di[dir];
					jline += dj[dir];
					if (iline < 0 || iline > 7 || jline < 0 || jline > 6) break;
					if (cells[iline][jline] != start) break;
				}
				if (lenght == 4) {
					winner = start;
					return;
				}
			}
		}
	}
}

bool Field::isOver() const{
	if (winner != EMPTY) return true;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			if (cells[i][j] == EMPTY) return false;
		}
	}
	cout << "Ходов больше нет, победила дружба :)" << endl;
	return true;
}

bool Field::isRedTurnNow() const {
	if (isRedTurn) return true;
	return false;
}

void Field::print() const {
	for (int j = 5; j > -1; j--) {
		cout << "  ";
		for (int i = 0; i < 7; i++) {
			cout << cells[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	return;
}

void Field::printResult() const {
	setlocale(LC_ALL, "Russian");
	print();
	cout << "Поздравляем! Победил" <<
		(isRedTurn ? " желтый " : " красный ") << "игрок!"<< endl;
}