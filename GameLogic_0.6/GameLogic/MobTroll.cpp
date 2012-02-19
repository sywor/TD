#include "MobTroll.h"

MobTroll::MobTroll(int _mobType, int _ID, Sounds* _mobSound) : Mob(_mobType, _ID, _mobSound){}

MobTroll::~MobTroll(){}

void MobTroll::Update(vector<Node*> _path, Graph* _graph)
{
	Mob::Update(_path, _graph);
}
