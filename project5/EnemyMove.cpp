#include "EnemyMove.h"
#include "_Debug/_DebugConOut.h"

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

	_startPos = _pos;					// 今の位置がｽﾀｰﾄ地点
	_endPos = _aim[_aimCnt].second;		// 最終地点

	// 
	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		break;
	default:
		AST();
		break;
	}

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
