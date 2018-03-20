#ifndef HUFF_H
#define HUFF_H

#include <iostream>
#include <vector>
#include <map>
#include "Node.h"

typedef std::vector<bool> MyCode;
MyCode code;
std::map<char, MyCode> table;

void BuildTable(Node* root);


#endif // HUFF_H
