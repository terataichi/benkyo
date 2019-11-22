#include "FuncBullet.h"
#include <bullet.h>


bool FuncBullet::operator()(ActQueT& actQue, std::vector<sharedObj>& _objList)
{
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER) ? UNIT_ID::PL_BULLET : UNIT_ID::EM_BULLET;
	_objList.emplace_back(new Bullet(unitID, actQue.second.pos()));

	return true;
}