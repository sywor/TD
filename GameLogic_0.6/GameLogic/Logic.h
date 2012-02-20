#ifndef _LOGIC_H 
#define _LOGIC_H

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "FireTower.h"
#include "SlowTower.h"
#include "MobTroll.h"
#include "Graph.h"
#include "Timer.h"
#include "Sounds.h"

using namespace std;

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

struct DrawableTower
{
	int type;
	D3DXVECTOR3 towerPos;
	D3DXVECTOR3 mobPos;
	bool hasTarget;

	DrawableTower(int _type, D3DXVECTOR3 _towerPos, D3DXVECTOR3 _mobPos)
	{
		type = _type;
		towerPos = _towerPos;
		mobPos = _mobPos;
		hasTarget = true;
	}

	DrawableTower(int _type, D3DXVECTOR3 _towerPos)
	{
		type = _type;
		towerPos = _towerPos;
		hasTarget = false;
	}
};

struct Player
{
	int score;
	int cash;
	string name;
};

struct Wave
{
	int numMob, mobType;

	Wave(int _num, int _type)
	{
		numMob = _num;
		mobType = _type;
	}
};

class Logic
{
private:
	vector<Mob*> mobs;
	vector<DrawableMob> mobsToDraw;
	vector<DrawableTower> towersToDraw;
	vector<Wave> waves;
	vector<Tower*> towers;

	vector<DrawableMob> SortAndCreatMobsDrawList();
	vector<DrawableTower> SortAndCreatTowerDrawList();
	void AddMobToCurrentWave(int _mobType, int _numMobs);

	Node*		root;
	Graph*		graph;
	Timer*		timer;
	Sounds*		sound;
	int			mobID;
	bool		waveCreat;
public:
	Logic();
	
	void frame();
};
#endif