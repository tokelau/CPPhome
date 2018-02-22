#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include "node.h"

typedef std::set<Node*>::const_iterator node_iterator;
class Graph {
	std::set<Node*> nodes;
	std::set<std::string> names;
	void addNode(Node* node);
	void removeNode(Node* node);
	node_iterator searchByName(std::string& aname);
public:
	Graph() {};
	Graph(Node* node) { nodes.insert(node); };
	Graph(const unsigned long int n);
	void add(std::string aname);
	void remove(std::string aname);
	void addEdge(std::string b, std::string e);
	void removeEdge(std::string b, std::string e);
	bool readNodes(const char* inFile);
	void print();
	node_iterator begin() const {
		return nodes.begin();
	}
	node_iterator end() const { 
		return nodes.end(); 
	}
	//std::string operator= (char ch) const;
protected:
	friend class BFS;
	friend class DFS;
};

#endif
