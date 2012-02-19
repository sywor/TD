#ifndef _GRAPH_H
#define _GRAPH_H


#include <vector>
#include "Node.h"
#include "SlowTower.h"
#include "FireTower.h"
#include <iostream>
#include <algorithm>

using namespace std;

class Graph
{
private:	
	vector<Node*> openNodes;
	void createEdge(int vectorPos1, int vectorPos2, int wheight);
	void update(Node* currentNode);
	void removeDuplicates();
	void addToList(Node* _root);
	void gridder();
	void sort();
	void sortHelper(vector<Node*> _tempList);
	Node* getNode(Node* _root, float _x, float _z);
	vector<Node*> findPath(Node* _startNode, Node* _targetNode);

	int					counter;
	Node*				targetNode;
	Node*				currentNode;
	vector<Node*>		tempNodeList;
	Node*				root;
	vector<Node*>		retRoute;

public:
	Graph(Node* _root);	
	vector<Node*> findPath(vector<Node*> _wayPoints);

	void setTower(Node* _node, Tower* _tower);
	Node* getNode(float _x, float _z);
	void setNeighbours();	
	vector<Node*>		nodeList;
};
#endif