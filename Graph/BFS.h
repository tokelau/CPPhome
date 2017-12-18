#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include "node.h"
#include <set>

class BFS {
	typedef std::set<Node*>::const_iterator node_iterator;
	Graph& graph;
public:
	BFS(Graph& agraph) : graph(agraph) {}
	bool connected(std::string b, std::string e) const;
};

#endif