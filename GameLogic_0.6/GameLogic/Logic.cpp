#include "Logic.h"

Logic::Logic()
{
	root = new Node(0, 0, 4096, 4096);
	graph = new Graph(root);
	timer = new Timer();
	sound = new Sounds();

	timer->reset();
	sound->initSounds();

	mobID = 0;
	waveCreat = false;

	int numwaves = 0; // läs från CFG!

	for (int i = 0; i < numwaves; i++)
	{
		int numMob = 0; // läs från CFG
		int mobType = 0; // läs från CFG
		//ADD FANCY PARSING!!! (V)(;,,;)(V)
		waves.push_back(Wave(numMob, mobType));
	}
}

void Logic::frame()
{
	SortAndCreatMobsDrawList();
	SortAndCreatTowerDrawList();
}

void Logic::AddMobToCurrentWave(int _mobType, int _numMobs)
{
	timer->tick();
	if (1.5f < timer->getTime())
	{
		switch(_mobType)
		{
		case 0:
			mobs.push_back(new MobTroll(_mobType, mobID, sound));
			break;
		}
		mobID++;
	}
	else
	{
		return;
	}

	if (mobs.size() == _numMobs)
	{
		timer->reset();
		waveCreat = false;
	}
}

vector<DrawableMob> Logic::SortAndCreatMobsDrawList()
{
	for (int i = 0; i < mobs.size(); i++)
	{
		for (int j = 0; j < mobs.size(); j++)
		{
			if (mobs[i]->MobType < mobs[j]->MobType)
			{
				Mob* temp = mobs[i];
				mobs[i] = mobs[j];
				mobs[j] = temp;
				temp = NULL;
			}
		}
	}

	mobsToDraw.clear();

	for (int i = 0; i < mobs.size(); i++)
	{
		mobsToDraw.push_back(DrawableMob(mobs[i]->MobType, mobs[i]->mobPos));
	}

	return mobsToDraw;
}

vector<DrawableTower> Logic::SortAndCreatTowerDrawList()
{
	for (int i = 0; i < towers.size(); i++)
	{
		for (int j = 0; j < towers.size(); j++)
		{
			if (towers[i]->towerType < towers[j]->towerType)
			{
				Tower* temp = towers[i];
				towers[i] = towers[j];
				towers[j] = temp;
				temp = NULL;
			}
		}
	}

	towersToDraw.clear();

	for (int i = 0; i < towers.size(); i++)
	{
		if (towers[i]->node->towerTarget != NULL)
		{
			towersToDraw.push_back(DrawableTower(towers[i]->towerType, towers[i]->node->pos, towers[i]->node->towerTarget->mobPos));
		} 
		else
		{
			towersToDraw.push_back(DrawableTower(towers[i]->towerType, towers[i]->node->pos));
		}
		
	}

	return towersToDraw;
}