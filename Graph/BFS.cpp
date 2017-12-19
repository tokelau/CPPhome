#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <queue>
#include "BFS.h"
#include "graph.h"

bool BFS::connected(std::string b, std::string e) const  {
	Node* begin = (*graph.searchByName(b));
	Node* end = (*graph.searchByName(e));
	std::queue<Node*> nodes; nodes.push(begin);
	std::set<Node*> visited;
	while (!nodes.empty()) {
		Node* next = nodes.front(); nodes.pop();
		if (end == next) return true;
		visited.insert(next);
		for (node_iterator it = next->nb_begin(); it != next->nb_end(); it++)
			if (visited.find(*it) == visited.end())
				nodes.push(*it);
	}
	return false;
}

void BFS::clustering() {
	std::string fileName = "out";
	//std::string i = "0";
	char i = 49;
	std::set<Node*> nodes;
	std::queue<Node*> visited;
	visited.push((*graph.begin()));
	for (node_iterator it = graph.begin(); it != graph.end(); it++) {
		/*может быть не соединен сам с собой, но быть в одном с собой кластере*/
		if ((*it)->name == visited.front()->name) continue;
		if (!connected(visited.front()->name, (*it)->name)) {
			nodes.insert((*it));
		}
		else {
			visited.push((*it));
			//std::cout << (*it)->name << ' ';
		}
	}
	writeCluster(fileName+".txt", visited);
	while (!nodes.empty()) {
		visited.push(*nodes.begin()); nodes.erase(*nodes.begin());
		for (node_iterator it = nodes.begin(); it != nodes.end(); it++) {
			if ((*it)->name == visited.front()->name) continue;
			if (connected(visited.front()->name, (*it)->name)) {
				visited.push((*it));
				nodes.erase(*it);
			}
		}
		writeCluster(fileName + i + ".txt", visited);
		i++;
	}

}

/*записывает кластер и очищает visited*/
bool BFS::writeCluster(std::string fileName, std::queue<Node*>& v) {
	std::ofstream out(fileName);
	if (!out.is_open()) return false;
	std::string s = "123";
	while (!v.empty()) {
		out << v.front()->name.c_str()<<" ";
		v.pop();
	}
	out.close();
	return true;
}