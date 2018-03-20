#include <iostream>
#include <map>
#include <list>
#include <vector>
#include "Node.h"
#include "Huffman.h"

using namespace std;

int main(void) {
	string str = "Amazing coder";
	map<char, int> m;
	for (string::iterator it = str.begin(); it != str.end(); it++) {
		m[(*it)]++;
	}

	/*список узлов*/
	list<Node*> tab;
	for (map<char, int>::iterator it = m.begin(); it != m.end(); it++) {
		Node* p = new Node;
		p->c = (*it).first;
		p->v = (*it).second;
	}
	/*кодовое дерево*/
	while (tab.size() > 1) {
		tab.sort(MySort());
		Node* sonL = tab.front();
		tab.pop_front();
		Node* sonR = tab.front();
		tab.pop_front();
		Node* parent = new Node(sonL, sonR);
		tab.push_back(parent);

	}

	Node* root = tab.front();
	BuildTable(root);

	system("pause");
	return 1;
}