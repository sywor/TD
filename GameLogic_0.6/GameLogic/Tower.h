#ifndef TOWER_H
#define TOWER_H
#include "Timer.h"
#include "Node.h"
#include "Sounds.h"

class Tower
{
protected:	
	int nodeID;
	double damage;
	float range;
	float fireRate;
	Timer* timer;
	void setTowerTarget();
	Sounds* towerSound;
public:
	Tower(int _nodeID, int _towerType, Sounds* _towerSound);
	virtual ~Tower();
	virtual void	Update() = 0;
	Node* node;
	float calcDist(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2);
	int towerType;

};
#endif