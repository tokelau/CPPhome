#include <set>
#include <queue>
#include "BFS.h"
#include "graph.h"
#include "DFS.h"

bool DFS::connected(std::string b, std::string e) {
	visited.clear(); 
	return connected(b, e, 0);
}

bool DFS::connected(std::string b, std::string e, int depth) {
	Node* begin = (*graph.searchByName(b));
	Node* end = (*graph.searchByName(e));
	if (begin == end) return true;
	visited.insert(begin);
	for (node_iterator it = begin->nb_begin(); it != begin->nb_end(); it++) {
		if (visited.find(*it) == visited.end()) {
			if (connected((*it)->name, e, depth + 1)) return true;
		}
	}
	return false;
}