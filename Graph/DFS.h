#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include "node.h"
#include <set>

class DFS {
	typedef std::set<Node*>::const_iterator node_iterator;
	Graph& graph;
	std::set<Node*> visited;
	bool connected(std::string b, std::string e, int depth);
public:
	DFS(Graph& agraph) : graph(agraph) {}
	bool connected(std::string b, std::string e);
};

#endif
