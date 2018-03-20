#include <iostream>
#include "Huffman.h"

void BuildTable(Node* root) {
	if (root->left) {
		code.insert(code.end(), 0);
		BuildTable(root->left);
	}
	if (root->right) {
		code.insert(code.end(), 1);
		BuildTable(root->right);
	}
	if (root->left == nullptr && root->right == nullptr) table[root->c] = code;
	code.pop_back();

}