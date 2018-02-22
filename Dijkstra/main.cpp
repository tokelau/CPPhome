#include <iostream>
#include "dkt.h"

using namespace std;

int main(void){
	vector<vector<pair<int, int>>> g;
	initVector(g);
	findWay(g);

	system("pause");
	return 0;
}