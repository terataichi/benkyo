#include "FuncBullet.h"
#include <algorithm>
#include "../../Bullet.h"
#include "../SceneMng.h"
#include "../GameScene.h"

std::map<UNIT_ID, int> FuncBullet::_MaxCount{ {UNIT_ID::PL_BULLET , 2} , {UNIT_ID::EM_BULLET , 2} };

bool FuncBullet::operator()(ActQueT& actQue, void* scene)
{
	// ÌßÚ²Ô°‚Ì’e‚©“G‚Ì’e‚©Œ©•ª‚¯‚éˆ—
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER) ? UNIT_ID::PL_BULLET : UNIT_ID::EM_BULLET;

	if (_MaxCount[unitID] > std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.end(), [&](sharedObj obj) {return (*obj).unitID() == unitID; }))
	{
		((GameScene*)scene)->_objList.emplace_back(new Bullet(unitID, actQue.second.pos()));

		return true;
	}

	return false;
}