#include <iostream>
#include <set>
#include "node.h"
#include "graph.h"
#include "BFS.h"
#include "DFS.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc < 3) {
		cout << "Not enough arguments" << endl;
		return -1;
	}
	Graph g;
	g.readNodes(argv[1]);

	g.add("56");
	g.addEdge("1", "56");
	g.print();

	g.removeEdge("1", "0");
	g.print();

	BFS bfs(g);
	cout << endl;
	cout << bfs.connected("1", "56") << endl;
	cout << bfs.connected("1", "0") << endl;

	DFS dfs(g);
	cout << endl;
	cout << dfs.connected("1", "56") << endl;
	cout << dfs.connected("1", "0") << endl;

	g.remove("0");
	g.print();

	system("pause");
	return 1;
}