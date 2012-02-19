#ifndef FIRETOWER_H
#define FIRETOWER_H

#include "Tower.h"
#include "Mob.h"



class FireTower : public Tower
{
private:
	int AOERange;
	double DOTdamage;
public:
	FireTower(int _nodeID, int _towerType, Sounds* _towerSound);
	virtual void Update();
	~FireTower();
};
#endif