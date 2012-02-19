#include "FireTower.h"

FireTower::FireTower(int _nodeID, int _towerType, Sounds* _towerSound) : Tower(_nodeID, _towerType, _towerSound)
{
	range = 2000.0f;
	damage = 10.0;
	DOTdamage = 1.0;
	fireRate = 1.2f;
	AOERange = 4;
}
void FireTower::Update()
{
	Tower::Update();

	if (fireRate <= timer->getTime() && node->towerTarget != NULL)
	{
		timer->reset();
		towerSound->PlaySounds(0);

		if (node->towerTarget->DOTCount < 0.5f)
		{
			node->towerTarget->life -= damage;
			node->towerTarget->DOT = DOTdamage;
			node->towerTarget->DOTCount = 1.0;
		}
		else
		{
			node->towerTarget->life -= damage;
			node->towerTarget->DOTCount += 0.1;
		}


		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < AOERange; j++)
			{
				Node* temp = node->towerTarget->currNode->getNeighbour(i, j);

				if (temp != NULL && !temp->nodeMobs.empty())
				{
					for (int k = 0; k <temp->nodeMobs.size(); k++)
					{
						if (node->towerTarget->DOTCount < 0.5f)
						{
							temp->nodeMobs[k]->life -= damage;
							temp->nodeMobs[k]->DOT = DOTdamage;
							temp->nodeMobs[k]->DOTCount = 1.0;
						}
						else
						{
							temp->nodeMobs[k]->life -= damage;
							temp->nodeMobs[k]->DOTCount += 0.1;
						}

					}
				}				
			}
		}
	}
}

FireTower::~FireTower(){}
