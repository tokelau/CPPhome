#ifndef DKT_H
#define DKT_H

#include <iostream>
#include <vector>

using namespace std;
const int INF = 100000000;

void initVector(vector<vector<pair<int, int>>> &g);
void findWay(vector<vector<pair<int, int>>> g);
void coutWay(vector<int> p);

#endif