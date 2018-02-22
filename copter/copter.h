#ifndef COPTER_H
#define COPTER_H

#include "field.h"

enum DIR {FORW = 0, RIGHT = 90, BACK = 180, LEFT = -90};

class Copter {
public:
	int way[16][2];
	DIR direction[16];
	int energy, builds;
	Field field_ans;
	void findField(Field field, int i, int j, int en, int bd);
	void findWay(int i, int j, int en);
	void printRes();
	Copter();
	//Copter(Field f);
private:

};

#endif
