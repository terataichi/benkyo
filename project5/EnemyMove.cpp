#include "EnemyMove.h"
#include <DxLib.h>

EnemyMove::EnemyMove(Vector2dbl& pos) :_pos(pos)
{
	_move = nullptr;
	_aimCnt = -1;		// 0だといきなりｱｸｾｽする
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
		_aim.clear();					//	要素を消すよ
	}

	_aim = std::move(state);			// 情報を格納する

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
