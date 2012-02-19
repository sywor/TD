#ifndef _MOBTROLL_H
#define _MOBTROLL_H

#include "Mob.h"

using namespace std;

class MobTroll : public Mob
{
private:

public:
	MobTroll(int _mobType, int _ID, Sounds* _mobSound);
	virtual void Update(vector<Node*> _path, Graph* _graph);
	~MobTroll();
};
#endif