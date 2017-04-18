#ifndef _CIRCUIT_H
#define _CIRCUIT_H

struct File {
	int px, row, column;
	char** In;
};

//пробегает по всему массиву
void findCircuit(File* arr, int lineNum, int columnNum);
//рекурсивно находит контур
void checkRec(File* arr, int lineNum, int columnNum);

#endif