#include "Tower.h"
#include <D3DX10.h>
#include "Mob.h"

Tower::Tower(int _nodeID, int _towerType, Sounds* _towerSound)
{
	nodeID = _nodeID;
	towerType = _towerType;
	timer = new Timer();
	timer->reset();
	towerSound = _towerSound;
}

void Tower::Update()
{
	timer->tick();

	if (node->towerTarget != NULL)
	{
		if (!node->towerTarget->alive)
		{
			node->towerTarget = NULL;
		}		
	}

	if (!node->towerTargets.empty())
	{
		for (int i = 0; i < node->towerTargets.size(); i++)
		{
			if (!node->towerTargets[i]->alive)
			{
				node->towerTargets.erase(remove(node->towerTargets.begin(), node->towerTargets.end(), node->towerTargets[i]), node->towerTargets.end());
			}
		}
	}

	setTowerTarget();
}

void Tower::setTowerTarget()
{
	int mobID = 0;
	float dist = 100000.0f;

	if (!node->towerTargets.empty())
	{
		dist = calcDist(node->towerTargets[0]->mobPos, node->pos);	

		for (int i = 0; i < node->towerTargets.size(); i++)
		{
			float temp = calcDist(node->towerTargets[i]->mobPos, node->pos);

			if (dist > temp)
			{
				dist = temp;
				mobID = i;
			}

			if (temp > range)
			{
				node->towerTargets.erase(remove(node->towerTargets.begin(), node->towerTargets.end(), node->towerTargets[i]), node->towerTargets.end());
			}
		}
	}

	if (dist < range)
	{
		node->towerTarget = node->towerTargets[mobID];
	}
	else
	{
		node->towerTarget = NULL;
	}
}

float Tower::calcDist(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2)
{
	D3DXVECTOR3 temp = (v2 - v1);
	return std::abs(std::sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z));
}

Tower::~Tower()
{

}