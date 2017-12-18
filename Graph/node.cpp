#include <iostream>
#include <set>
#include "node.h"
#include "graph.h"

/*добавить соседа*/
void  Node::addNeighbour(Node* neighbour) {
	//std::cout << this->name << " " << neighbour->name << " " << this<<" "<<neighbour;
	//std::cout<<std::endl;
	neighbours.insert(neighbour);
}

/*удалить соседа*/
void Node::removeNeighbour(Node* neighbour) {
	neighbours.erase(neighbour);
}

void Node::print() {
	std::cout << "name: " << name << std::endl;
	if (neighbours.empty()) {
		std::cout << "Set of neighbours is empty. ";
	}
	for (node_iterator it = nb_begin(); it != nb_end(); it++) {
		Node* temp = *it;
		std::cout << temp->name << " ";
	}
	std::cout << std::endl;
}

std::ostream& operator<< (std::ostream& out, const std::string& s) {
	for (unsigned int i = 0; i < s.length(); i++) {
		std::cout << s[i];
	}
	return out;
}