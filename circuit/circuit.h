#ifndef _CIRCUIT_H
#define _CIRCUIT_H

struct File {
	int px, row, column;
	char** In;
};

//��������� �� ����� �������
void findCircuit(File* arr, int lineNum, int columnNum);
//���������� ������� ������
void checkRec(File* arr, int lineNum, int columnNum);

#endif