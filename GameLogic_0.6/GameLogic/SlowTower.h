#ifndef SLOWTOWER_H 
#define SLOWTOWER_H

#include "Tower.h"

class SlowTower : public Tower
{
private:
	Sounds* slowSound;
public:
	SlowTower(int _nodeID, int _towerType, Sounds* _slowSound);
	virtual void Update();
	~SlowTower();
};
#endif