#include "Graph.h"

Graph::Graph(Node* _root)
{
	//root = new Node(0, 0, 4092, 4092);
	counter = 0;

	for (int i = 0; i < 3; i++)
	{
		_root->SubDivide();
	}

	addToList(_root);
	removeDuplicates();	
	sort();
	gridder();
	setNeighbours();
}

#pragma region Init

void Graph::removeDuplicates()
{
	for (int i = 0; i < tempNodeList.size(); i++)
	{
		for (int j = 0; j < tempNodeList.size(); j++)
		{
			if (tempNodeList[i]->upperLeftX == tempNodeList[j]->upperLeftX && tempNodeList[i]->upperLeftZ == tempNodeList[j]->upperLeftZ)
			{
				tempNodeList.erase(tempNodeList.begin() + j);
			}			
		}
	}
}

void Graph::addToList(Node* _root)
{
	for (int i = 0; i < 4; i++)
	{
		if (_root->subNode != NULL)
		{
			addToList(_root->subNode[i]);
		} 
		else
		{
			tempNodeList.push_back(_root);
		}
	}
}

void Graph::gridder()
{
	int widthCounter = 0;
	int width =  (int)std::sqrt((double)nodeList.size());

	for (int i = 0; i < nodeList.size(); i++)
	{
		if (i + 1 < nodeList.size() && nodeList[i + 1] != NULL && widthCounter < width - 1)
		{
			nodeList[i] ->addEdge(nodeList[i + 1]);
		}

		if (i - 1 > -1 && nodeList[i - 1] != NULL && widthCounter != 0)
		{
			nodeList[i] ->addEdge(nodeList[i - 1]);
		}

		if (i + width < nodeList.size() && nodeList[i + width] != NULL)
		{
			nodeList[i] ->addEdge(nodeList[i + width]);
		}

		if (i - width > -1 && nodeList[i - width] != NULL)
		{
			nodeList[i] ->addEdge(nodeList[i - width]);
		}
		widthCounter++;

		if (widthCounter == width)
		{
			widthCounter = 0;
		}
	}

	/*
	Kopplings schema:

	#	3	#
	1	*	0
	#	2	#

	*/
}

void Graph::sort()
{
	Node* temp2 = NULL;
	vector<Node*> tempList;
	int pointer;

	for (int i = 0; i < tempNodeList.size(); i++)
	{
		for (int j = 0; j < tempNodeList.size(); j++)
		{
			if (tempNodeList[i]->upperLeftZ < tempNodeList[j]->upperLeftZ)
			{
				Node* temp = tempNodeList[i];
				tempNodeList[i] = tempNodeList[j];
				tempNodeList[j] = temp;
			}
		}
	}

	temp2 = tempNodeList[0];

	for (int i = 0; i < tempNodeList.size(); i++)
	{
		if (tempNodeList[i]->upperLeftZ == temp2->upperLeftZ)
		{
			tempList.push_back(tempNodeList[i]);
		} 
		else
		{
			temp2 = tempNodeList[i];
			i--;
			sortHelper(tempList);	
			tempList.clear();
		}

		if (i == tempNodeList.size() - 1)
		{
			sortHelper(tempList);
		}
	}

	for (int i = 0; i < nodeList.size(); i++)
	{
		nodeList[i]->ID = i;
	}
}

void Graph::sortHelper(vector<Node*> _tempList)
{
	for (int j = 0; j < _tempList.size(); j++)
	{
		for (int k = 0; k < _tempList.size(); k++)
		{
			if (_tempList[j]->upperLeftX < _tempList[k]->upperLeftX)
			{
				Node* temp = _tempList[j];
				_tempList[j] = _tempList[k];
				_tempList[k] = temp;
			}
		}
	}

	for (int j = 0; j < _tempList.size(); j++)
	{
		nodeList.push_back(_tempList[j]);
	}	
}

void Graph::setNeighbours()
{
	for (int j = 0; j < nodeList.size(); j++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int k = 0; k < 6; k++)
			{
				nodeList[j]->neighbours[i][k] = nodeList[j]->getNeighbour(i,k);
			}
		}
	}

}

#pragma endregion 

void Graph::setTower(Node* _node, Tower* _tower)
{
	_node->setWeight(10000);
	_node->tower = _tower;
	_tower->node = _node;
}

vector<Node*> Graph::findPath(vector<Node*> _wayPoints)
{
	vector<Node*> res;
	vector<Node*> temp;

	for (int i = 0; i < _wayPoints.size() - 1; i++)
	{
		temp = findPath(_wayPoints[i], _wayPoints[i + 1]);

		for (int i = 0; i < nodeList.size(); i++)
		{
			nodeList[i]->visited = false;
			nodeList[i]->totalWeight = -1;
			nodeList[i]->originNode = -1;
		}

		for (int i = 0; i < temp.size(); i++)
		{
			res.push_back(temp[i]);
		}
		retRoute.clear();
	}
	res.erase(std::unique(res.begin(), res.end()),res.end());
	return res;
}

vector<Node*> Graph::findPath(Node* _startNode, Node* _targetNode)
{
	openNodes.push_back(_startNode);
	_startNode->totalWeight = 0;
	

	while(!openNodes.empty())
	{
		_startNode = openNodes[0];

		for(int i = 1; i < openNodes.size(); i++)
		{
			if(openNodes[i]->totalWeight < _startNode->totalWeight)
			{
				_startNode = openNodes[i];
			}
		}

		update(_startNode);

		if(_startNode->ID == _targetNode->ID)
		{
			break;
		}
	}

	while(_startNode->originNode != -1)
	{
		retRoute.push_back(_startNode);
		_startNode = nodeList[_startNode->originNode];
	}

	retRoute.push_back(_startNode);
	std::reverse(retRoute.begin(), retRoute.end());
	openNodes.clear();
	return retRoute;
}

void Graph::update(Node* _currentNode)
{
	for(int i = 0; i < _currentNode->edges.size(); i++)
	{
		if(!_currentNode->edges[i]->visited)
		{
			int temp = _currentNode->totalWeight + _currentNode->edges[i]->weight;

			if(_currentNode->edges[i]->totalWeight < 0 || temp < _currentNode->edges[i]->totalWeight)
			{
				_currentNode->edges[i] -> originNode = _currentNode -> ID;
				_currentNode->edges[i] -> totalWeight = temp;				
				openNodes.push_back(_currentNode -> edges[i]);
			}
		}
	}
	_currentNode->visited = true;
	
	openNodes.erase(std::remove(openNodes.begin(), openNodes.end(), _currentNode),openNodes.end());
}

Node* Graph::getNode(float _x, float _z)
{
	for (int i = 0; i < 4; i++)
	{
		int left = root->subNode[i]->upperLeftX;
		int right = root->subNode[i]->upperLeftX + root->subNode[i]->width;
		int top = root->subNode[i]->upperLeftZ;
		int bottom = root->subNode[i]->upperLeftZ + root->subNode[i]->height;

		if (_x < right && _x > left && _z < bottom && _z > top)
		{
			return getNode(root->subNode[i], _x, _z);
		}
	}
}

Node* Graph::getNode(Node* _root, float _x, float _z)
{
	for (int i = 0; i < 4; i++)
	{
		if (_root->subNode != NULL)
		{
			int left = _root->subNode[i]->upperLeftX;
			int right = _root->subNode[i]->upperLeftX + _root->subNode[i]->width;
			int top = _root->subNode[i]->upperLeftZ;
			int bottom = _root->subNode[i]->upperLeftZ + _root->subNode[i]->height;

			if (_x < right && _x > left && _z < bottom && _z > top)
			{
				return getNode(_root->subNode[i], _x, _z);
			}
		}
		else
		{
			return _root;
		}
	}
}


