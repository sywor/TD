#include "Node.h"
#include "MobTroll.h"

Node::Node(long _upperLeftX, long _upperLeftY, long _width, long _height)
{
	upperLeftX = _upperLeftX;
	upperLeftZ = _upperLeftY;
	width = _width;
	height = _height;
	subNode = NULL;
	ID = 0;
	pos.x = upperLeftX;
	pos.z = upperLeftZ;
	pos.y = 1.0f;
	originNode = -1;
	totalWeight = -1;
	weight = 1;
	visited = false;
	towerTarget = NULL;
	subNode = NULL;
	tower = NULL;
	//towerTargets = new vector<Mob*>();
}

HRESULT Node::SubDivide()
{
	HRESULT result = S_OK;

	if(!subNode)
	{
		long w = width / 2;
		long h = height / 2;
		long ulx = upperLeftX;
		long uly = upperLeftZ;

		subNode = (Node**)::CoTaskMemAlloc(4 * sizeof(Node*));

		subNode[0] = new Node(ulx, uly, w, h);
		subNode[1] = new Node(ulx + w, uly, w, h);
		subNode[2] = new Node(ulx, uly + h, w, h);
		subNode[3] = new Node(ulx + w, uly + h, w, h);

	}
	else
	{
		for (int i = 0; i < 4 && SUCCEEDED(result); i++) 
		{
			result = subNode[i]->SubDivide();
		}
	}
	return result;
}

void Node::catchMob(Mob* _mob)
{
	bool insert = true;

	for (int i = 0; i < towerTargets.size(); i++)
	{
		if (towerTargets[i]->ID == _mob->ID)
		{
			insert = false;
		}
	}

	if (insert)
	{
		towerTargets.push_back(_mob);
	}
}

void Node::setWeight(int _weight)
{
	weight = _weight;
}

void Node::addEdge(Node* _Node)
{
	edges.push_back(_Node);
}

Node* Node::getNeighbour(int _dir, int _num)
{
	if (_num == 0 && edges.size() > _dir)
	{
		return edges[_dir];
	}
	else if (edges.size() <= _dir)
	{
		return NULL;
	}
	else
	{
		_num--;
		getNeighbour(_dir, _num);
	}
}

void Node::updateTower()
{
	for (int i = 0; i < 4; i++)
	{
		if (subNode != NULL)
		{
			subNode[i]->updateTower();
		} 
		else if (tower != NULL)
		{
			tower->Update();
		}
	}
}

void Node::setNodeMob(Mob* _mob)
{
	bool insert = true;

	for (int i = 0; i < nodeMobs.size(); i++)
	{
		if (nodeMobs[i]->ID == _mob->ID)
		{
			insert = false;
		}
	}

	if (insert)
	{
		nodeMobs.push_back(_mob);
	}
}