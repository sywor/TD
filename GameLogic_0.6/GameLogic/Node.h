#ifndef _NODE_H
#define _NODE_H

#include <vector>
#include <Windows.h>
#include <D3DX10.h>

using namespace std;
class Mob;
class Tower;

class Node
{
public:

	Node(long _lowerLeftX, long _lowerLeftY, long _width, long _height);	
	void setWeight(int _weight);
	void addEdge(Node* _Node);
	void findNerestMob();
	void catchMob(Mob* _mob);
	Node* getNeighbour(int _dir, int _num);
	void updateTower();
	HRESULT	SubDivide();
	void setNodeMob(Mob* _mob);

	D3DXVECTOR3		pos;
	Node*			neighbours[4][6];
	vector<Node*>	edges;			
	Node**			subNode;
	long			upperLeftX;
	long			upperLeftZ;
	long			width;
	long			height;  
	int				ID;
	int				weight;
	int				originNode;
	int				totalWeight;
	bool			visited;
	Tower*			tower;
	vector<Mob*>	towerTargets;
	vector<Mob*>	nodeMobs;
	Mob*			towerTarget;
};
#endif