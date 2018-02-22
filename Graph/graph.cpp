#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include "graph.h"

Graph::Graph(const unsigned long int n) {
	char* aname = "";
	for (unsigned long int i = 0; i < n; i++) {
		std::cout << "Input name of node number " << i + 1 << ": ";
		std::cin >> aname;
		std::cout << std::endl;
		Node tmp(aname);
	}
}

bool Graph::readNodes(const char* inFile) {
	//std::cout << in << ' ' << out << std::endl;
	std::ifstream in(inFile);
	if (!in.is_open()) return 0;
	std::string aname1, aname2;
	while (!in.eof()) {
		std::getline(in, aname1, ' ');
		Node* temp;
		node_iterator it;
		it = searchByName(aname1);
		if (it == end()) {
			temp = new Node(aname1);
			addNode(temp);
		}
		else {
			temp = (*it);
		}
		std::getline(in, aname2, '\n');
		Node* temp2;
		it = searchByName(aname2);
		if (it == end()) {
			temp2 = new Node(aname2);
			addNode(temp2);
		}
		else {
			temp2 = (*it);
		}
		addEdge(temp->name, temp2->name);
		//std::cout << "s1: " << aname1 << " s2: " << aname2 << std::endl;
	}
	return 1;
}

/*добавить ноду в граф (private)*/
void Graph::addNode(Node* node) {
	if (!names.empty() && names.find(node->name) != names.end()) {
		return;
	}
	names.insert(node->name);
	nodes.insert(node);
	return;
}

/*добавить ноду в граф (public)*/
void Graph::add(std::string aname) {
	if (names.find(aname) != names.end()) {
		std::cout << "Rename your node: ";
		std::cin >> aname;
	}
	Node* temp = new Node(aname);
	addNode(temp);
	return;
}

/*удалить ноду из графа(private)*/
void Graph::removeNode(Node* node) {
	nodes.erase(node);
	// Remove also from all neighbours list
	for (std::set<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		/*удаление node из множества соседей it*/
		(*it)->removeNeighbour(node);
	}
}

/*удалить ноду из графа (public)*/
void Graph::remove(std::string aname) {
	if (names.find(aname) == names.end()) {
		std::cout << "Can't remove node. This does not exist. " << std::endl;
		return;
	}
	Node* temp = (*searchByName(aname));
	removeNode(temp);
	return;
}

/*добавить связь*/
void Graph::addEdge(std::string b, std::string e) {
	node_iterator begin = searchByName(b);
	node_iterator it = searchByName(e);
	if (begin == end() || it == end()) {
		std::cout << "Can't add the edge. There are no such vertices :( " << std::endl;
		return;
	}
	(*begin)->addNeighbour((*it));
	(*it)->addNeighbour((*begin));
}

/*удалить связь*/
void Graph::removeEdge(std::string b, std::string e) {
	node_iterator begin = searchByName(b);
	node_iterator it = searchByName(e);
	if (begin == end() || it == end()) {
		std::cout << "Can't remove the edge. There are no such vertices :( " << std::endl;
	}
	(*begin)->removeNeighbour((*it));
	(*it)->removeNeighbour((*begin));
}

/*возвращает ссылку на ноду, если есть с таким именем, иначе на конец множества*/
node_iterator Graph::searchByName(std::string& aname) {
	for (std::set<Node*>::iterator it = begin(); it != end(); it++) {
		if ((*it)->name == aname) {
			return it;
		}
	}
	return end();
}

void Graph::print() {
	std::cout << "  ";
	//for (unsigned int i = 0; i < nodes.size(); i++) {
	//	std::cout << i << " ";
	//}
	for (std::set<Node*>::iterator it = begin(); it != end(); it++) {
		std::cout << (*it)->name << ' ';
	}
	std::cout << '\n';
	unsigned int i = 0;
	for (std::set<Node*>::iterator it = begin(); it != end(); it++) {
		std::cout << (*it)->name << ' ';
		//std::cout << i << " ";
		for (std::set<Node*>::iterator it1 = begin(); it1 != end(); it1++) {
			//std::cout << (*it)->name << (*it1)->name<<" ";
			if ((*it)->neighbours.find(*it1) == (*it)->neighbours.end()) {
				std::cout << 0 << ' ';
			}
			else {
				std::cout << 1 << ' ';
			}
		}
		std::cout << '\n';
		i++;
	}
}