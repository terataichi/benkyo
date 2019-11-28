#include "FuncCheckHit.h"


bool FuncCheckHit::operator()(ActQueT & actQue, std::vector<sharedObj>& objList)
{
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PL_BULLET) ? UNIT_ID::ENEMY : UNIT_ID::PLAYER;


	for (auto obj : objList)
	{
		// ID�ƈ�v�����瓖���蔻�肵�Ă�����
		if ((*obj).unitID() == unitID && (*obj).isAlive())
		{
			_posLength = (actQue.second.pos().x - (*obj).pos().x) * (actQue.second.pos().x - (*obj).pos().x) + (actQue.second.pos().y - (*obj).pos().y) * (actQue.second.pos().y - (*obj).pos().y);
			_sizeLength = (((*obj).size().x - 15) * ((*obj).size().x - 15)) + (((*obj).size().y - 15) * ((*obj).size().y -15));

			// �����蔻��
			if (_posLength < _sizeLength)
			{
				(*obj).SetAlive(false);
				actQue.second.SetAlive(false);
				return true;
			}
		}
	}
	return false;
}
