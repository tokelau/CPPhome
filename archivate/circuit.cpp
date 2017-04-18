#include <iostream>
#include "circuit.h"
#include "file.h"

using namespace std;

void findCircuit(File* arr, int lineNum, int columnNum) {
	for (int i = lineNum; i < arr->row; i++) {
		for (int j = columnNum; j < arr->column; j++) {
			if (arr->In[i][j] == '1') {
				if (i == 0 || i == arr->row - 1 || j == 0 || j == arr->column - 1) {
					arr->In[i][j] = '2';
					writeCoordinates("coordinates.txt", i, j);
				}
				else if (arr->In[i][j - 1] == '0') {
					checkRec(arr, i, j);
				}
			}
		}
	}
	cout << "Circuit coordinates successfully saved..." << endl;
}

bool check(const File arr, int lineNum, int columnNum) {
	if (arr.In[lineNum][columnNum + 1] == '0' || arr.In[lineNum + 1][columnNum + 1] == '0' ||
	arr.In[lineNum + 1][columnNum] == '0' || arr.In[lineNum - 1][columnNum - 1] == '0'){
		return 1;
	}
	if (arr.In[lineNum][columnNum - 1] == '0' || arr.In[lineNum + 1][columnNum - 1] == '0' ||
		arr.In[lineNum - 1][columnNum + 1] == '0' || arr.In[lineNum - 1][columnNum] == '0') {
		return 1;
	}
	return 0;
}

void checkRec(File* arr, int lineNum, int columnNum) {
	if (arr->In[lineNum][columnNum] == '2') {
		return;
	}
	if (arr->In[lineNum][columnNum] == '0') {
		return;
	}
	if (lineNum == 0 || lineNum == arr->row-1) {
		return;
	}
	if (columnNum == 0 || columnNum == arr->column-1) {
		return;
	}
	if (check(*arr, lineNum, columnNum)) {
		arr->In[lineNum][columnNum] = '2';
		writeCoordinates("coordinates.txt", lineNum, columnNum);
		checkRec(arr, lineNum, columnNum + 1);
		checkRec(arr, lineNum, columnNum - 1);
		checkRec(arr, lineNum + 1, columnNum + 1);
		checkRec(arr, lineNum + 1, columnNum);
		checkRec(arr, lineNum + 1, columnNum - 1);
		checkRec(arr, lineNum - 1, columnNum + 1);
		checkRec(arr, lineNum - 1, columnNum);
		checkRec(arr, lineNum - 1, columnNum - 1);
	}
	return;
}