#include <iostream>
#include <set>
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