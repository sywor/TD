#include "Mob.h"


Mob::Mob(int _MobType, int _ID, Sounds* _mobSound)
{
	MobType = _MobType;
	mobPos = D3DXVECTOR3();
	timer = new Timer();
	timerDOT = new Timer();
	timer->reset();
	timerDOT->reset();
	nextNode = NULL;
	listCounter = 1;
	speed = 10.0f;
	alive = true;
	life = 1000;
	DOTCount = 0.0;
	ID = _ID;
	mobSound = _mobSound;
}

Mob::~Mob(){}

void Mob::ShootMe(Graph* _graph)
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			if (nextNode->neighbours[j][i] != NULL && nextNode->neighbours[j][i]->tower != NULL)
			{
				nextNode->neighbours[j][i]->catchMob(this);
			}				
		}		
	}	
}

void Mob::Update(vector<Node*> _path, Graph* _graph)
{
	

	if (DOTCount > 0)
	{
		timer->tick();
		timerDOT->tick();

		if (1.0f <= timerDOT->getTime())
		{
			life -= DOT;
			timerDOT->reset();
		}

		float time = timer->getTime();

		if ((3.0f * DOTCount) < time)
		{
			DOTCount = 0;
			timer->reset();
		}
	}

	if (nextNode == NULL)
	{
		nextNode = _path[1];
		mobPos.x = _path[0]->pos.x;
		mobPos.z = _path[0]->pos.z;
		mobPos.y = 1.0f;
	}

	int currNodeID;

	for (int i = 0; i < _path.size(); i++)
	{
		if (_path[i]->ID == nextNode->ID)
		{
			if (i == 0)
			{
				currNodeID = i;
				break;
			}
			else
			{
				currNodeID = i - 1;
				break;
			}

		}
	}

	currNode = _path[currNodeID];

	currNode->setNodeMob(this);

	float deltaX = nextNode->pos.x - mobPos.x;
	float deltaZ = nextNode->pos.z - mobPos.z;

	
	if ((std::abs((double)deltaX) < 10.0f && std::abs((double)deltaZ) < 10.0f))
	{	
		listCounter++;

		if (_path.size() > listCounter)
		{
			currNode->nodeMobs.erase(remove(currNode->nodeMobs.begin(), currNode->nodeMobs.end(), this), currNode->nodeMobs.end());
			currNode = nextNode;
			nextNode = _path[listCounter];
		}		
	}

	if (nextNode->pos.x < mobPos.x)
	{
		mobPos.x -= speed;
	}
	if (nextNode->pos.x > mobPos.x)
	{
		mobPos.x += speed;
	}
	if (nextNode->pos.z < mobPos.z)
	{
		mobPos.z -= speed;
	}
	if (nextNode->pos.z > mobPos.z)
	{
		mobPos.z += speed;
	}
	
	if (life <= 0)
	{
		alive = false;
		mobSound->PlaySounds(1);
	}

	ShootMe(_graph);
}

void Mob::removeMe()
{
	currNode->towerTarget = NULL;
	currNode->nodeMobs.erase(remove(currNode->nodeMobs.begin(), currNode->nodeMobs.end(), this), currNode->nodeMobs.end());
	delete this;
}