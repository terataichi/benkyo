#include "FuncBullet.h"
#include <bullet.h>


bool FuncBullet::operator()(ActQueT actQue, std::vector<sharedObj> _objList)
{
	for (auto actQue : actList)
	{
		switch (actQue.first)
		{
		case ACT_QUE::SHOT:
			UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER) ? UNIT_ID::PL_BULLET : UNIT_ID::EM_BULLET;
			_objList.emplace_back(new Bullet(unitID, actQue.second.pos()));
			break;
		}
	}
	return true;
}