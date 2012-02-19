#ifndef _LOGIC_H 
#define _LOGIC_H


#include <vector>
#include "FireTower.h"
#include "SlowTower.h"
#include "MobTroll.h"
#include "Graph.h"

using namespace std;

class Logic
{
private:
	vector<Mob*> mobs;
public:
	Logic();	
	void frame();
};

struct Player
{
	int score;
	int cash;
	string name;
};

struct DrawableMob
{
	int type;
	D3DXVECTOR3 pos;

	DrawableMob(int _type, D3DXVECTOR3 _pos)
	{
		type = _type;
		pos = _pos;
	}
};
#endif