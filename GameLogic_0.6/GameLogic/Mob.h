#ifndef _MOB_H
#define _MOB_H
#include "Graph.h"
#include "Sounds.h"
#include <D3DX10.h>
class Graph;
class Mob
{
private:
	int listCounter;
protected:	
	Timer* timerDOT;	
	float speed;
	Sounds* mobSound;
public:
	Mob(int _mobType, int _ID, Sounds* _mobSound);
	void ShootMe(Graph* _graph);
	virtual ~Mob();
	virtual void	Update(vector<Node*> _path, Graph* _graph) = 0;
	D3DXVECTOR3 mobPos;	
	int life, DOT;
	bool alive, DOTEnabled;
	Node* nextNode;
	Node* currNode;
	void removeMe();
	int ID;
	float DOTTime;
	Timer* timer;
	int MobType;
};
#endif