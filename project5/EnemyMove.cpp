#include "EnemyMove.h"
#include <DxLib.h>

EnemyMove::EnemyMove(Vector2dbl& pos) :_pos(pos)
{
	_move = nullptr;
	_aimCnt = -1;		// 0���Ƃ����Ȃ豸������
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	int a = 30;
	_pos.x += (rand() % a);
	_pos.x -= (rand() % a);
	_pos.y += (rand() % a);
	_pos.y -= (rand() % a);

}

bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	if (newFlag)
	{
		_aim.clear();					//	�v�f��������
	}

	_aim = std::move(state);			// �����i�[����

	if (newFlag)
	{
		SetMovePrg();
	}

	return true;
}

void EnemyMove::SetMovePrg(void)
{
	_aimCnt++;
	if (_aimCnt >= _aim.size())
	{
		return;
	}
	_startPos = _pos;



}

void EnemyMove::MoveSigmoid(void)
{

}

void EnemyMove::MoveSpiral(void)
{

}

void EnemyMove::PitIn(void)
{

}

void EnemyMove::Wait(void)
{

}

void EnemyMove::MoveLR(void)
{
}
