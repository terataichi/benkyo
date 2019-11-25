#include "FuncBullet.h"
#include <algorithm>
#include <bullet.h>

std::map<UNIT_ID, int> FuncBullet::_MaxCount{ {UNIT_ID::PL_BULLET , 2} , {UNIT_ID::EM_BULLET , 2} };

bool FuncBullet::operator()(ActQueT& actQue, std::vector<sharedObj>& objList)
{
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER) ? UNIT_ID::PL_BULLET : UNIT_ID::EM_BULLET;

	if (_MaxCount[unitID] > std::count_if(objList.begin(), objList.end(), [&](sharedObj obj) {return (*obj).unitID() == unitID; }))
	{
		objList.emplace_back(new Bullet(unitID, actQue.second.pos()));
		return true;
	}

	return false;
}