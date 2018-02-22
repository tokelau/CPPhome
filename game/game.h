#ifndef GAME_H
#define GAME_H

enum Cell {
	EMPTY,
	RED,
	YELLOW
};

//ширина 7, высота 6

class Field{
public:
	Cell cells[7][6];
	bool isRedTurn;
	Cell winner;

	Field(bool isRedFirst);
	void clear(bool isRedFirst);
	bool makeTurn(int column);
	void checkWinner();
	bool isOver() const;
	bool isRedTurnNow() const;
	void print() const;
	void printResult() const;
};

#endif