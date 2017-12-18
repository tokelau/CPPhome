#ifndef NODE_H
#define NODE_H

#include <set>

/*узел хранит в себе имя и множество указателей на своих соседей*/
class Node {
	typedef std::set<Node*>::const_iterator node_iterator;
	std::string name;
	std::set<Node*> neighbours;
public:
	Node() {};
	Node(const std::string& aname) : name(aname) {}
	void setName(std::string aname) { name = aname; }
	void addNeighbour(Node* neighbour);
	void removeNeighbour(Node* neighbour);
	void print();
	node_iterator nb_begin() const {
		return neighbours.begin();
	}
	node_iterator nb_end() const {
		return neighbours.end();
	}
	friend std::ostream& operator <<(std::ostream& out, const std::string& s);
protected:
	friend class Graph;
	friend class DFS;
};

#endif