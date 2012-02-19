#include <Windows.h>
#include <iostream>
#include <string>
#include "Graph.h"
#include "MobTroll.h"
#include "Timer.h"
#include <math.h>
#include "Sounds.h"


using namespace std;

Node* root = new Node(0, 0, 4092, 4092);
Graph* graph = new Graph(root);
Timer* timer = new Timer();
Sounds* sound = new Sounds();

int main()
{

	cout << graph->nodeList.size() << endl << endl;
	timer->reset();
	//for (int i = 0; i < graph->nodeList.size(); i++)
	//{
	//	for (int j = 0; j < graph->nodeList[i]->edges.size(); j++)
	//	{
	//		cout << graph->nodeList[i]->ID << " : " << graph->nodeList[i]->edges[j]->ID << endl;
	//	}
	//	cout << "_____________________" << endl;
	//}

	vector<Node*> tehList;

	graph->nodeList[32]->setWeight(10000);
	graph->nodeList[33]->setWeight(10000);
	graph->nodeList[34]->setWeight(10000);
	graph->nodeList[36]->setWeight(10000);
	graph->nodeList[37]->setWeight(10000);
	graph->nodeList[38]->setWeight(10000);
	graph->nodeList[39]->setWeight(10000);

	tehList.push_back(graph->nodeList[0]);
	tehList.push_back(graph->nodeList[17]);
	tehList.push_back(graph->nodeList[21]);
	tehList.push_back(graph->nodeList[61]);

	vector<Node*> res = graph->findPath(tehList);
	vector<Mob*> mobs;
	mobs.push_back(new MobTroll(0, 0, sound));

	FireTower* tower1 = new FireTower(9, 0, sound);
	FireTower* tower2 = new FireTower(10, 0, sound);
	FireTower* tower3 = new FireTower(11, 0, sound);
	FireTower* tower4 = new FireTower(12, 0, sound);
	FireTower* tower5 = new FireTower(13, 0, sound);

	graph->setTower(graph->nodeList[9], tower1);
	graph->setTower(graph->nodeList[10], tower2);
	graph->setTower(graph->nodeList[11], tower3);
	graph->setTower(graph->nodeList[12], tower4);
	graph->setTower(graph->nodeList[13], tower5);

	sound->initSounds();

	float dist = 0.0f;
	int ticker = 1;
	while(true)
	{
		timer->tick();

		if (timer->getTime() > 2.0f && mobs.size() < 5)
		{
			timer->reset();
			mobs.push_back(new MobTroll(0, ticker, sound));
			ticker++;
		}

		for (int i= 0; i < mobs.size(); i++)
		{
			mobs[i]->Update(res, graph);
		}

		root->updateTower();
		
		for (int i = 0; i < mobs.size(); i++)
		{
			cout << "X: " << mobs[i]->mobPos.x <<  " \tZ: " << mobs[i]->mobPos.z  << "\tID: " << mobs[i]->ID << " \tLife: " << ceil(mobs[i]->life) << "\tCurrNode: " << mobs[i]->currNode->ID << " \tNextNode: " << mobs[i]->nextNode->ID << "\t DotCount: " << mobs[i]->DOTCount<< endl;

			if (!mobs[i]->alive)
			{
				Mob* temp = mobs[i];
				mobs.erase(remove(mobs.begin(), mobs.end(), mobs[i]), mobs.end());
				temp->removeMe();
			}
		}

		cout << endl << "__________________________________________________________________________________" << endl << endl;

		for (int i = 0; i < graph->nodeList.size(); i++)
		{
			cout << "ID: " << graph->nodeList[i]->ID;

			if (!graph->nodeList[i]->towerTargets.empty())
			{
				cout << "\tTargets";

				for (int j = 0; j < graph->nodeList[i]->towerTargets.size(); j++)
				{
					cout << "\t: " << graph->nodeList[i]->towerTargets[j]->ID;
				}

				cout << endl;
			}
			else
			{
				cout << "\tTargets: NULL" << endl;
			}
		}
		

		system("cls");




	}

	system("PAUSE");
}