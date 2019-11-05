#include "EnemyMove.h"
#include "_Debug/_DebugConOut.h"

EnemyMove::EnemyMove(Vector2dbl& pos) :_pos(pos)
{
	_move = nullptr;
	_aimCnt = -1;						// 0だといきなりｱｸｾｽする
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{

	if (_move != nullptr)					// 中身があるかないかチェックする
	{
		(this->*_move)();					// 優先度をつけるためにかっこをつけないといけない
											// つけないとthis->(*_move())なってしまう。
	}

	//int a = 30;
	//_pos.x += (rand() % a);
	//_pos.x -= (rand() % a);
	//_pos.y += (rand() % a);
	//_pos.y -= (rand() % a);

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

	// firstの中のTYPEによって動き方を変える
	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
		count = 0;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		break;
	case MOVE_TYPE::PITIN:
		// どこに格納するのか決める
		_aim[_aimCnt].second.x = 50 + ();
		_aim[_aimCnt].second.y = (35 * 7) + ();
		_move = &EnemyMove::PitIn;
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		break;
	default:
		AST();
		_move = &EnemyMove::Wait;
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
	// 移動


	// 格納し終わったら切り替える
	if (_pos == _endPos)
	{
		SetMovePrg();
	}
}

void EnemyMove::Wait(void)
{
	count++;
	// 終端地点に来たら切り替える
	if (count > _aim[_aimCnt].second.x)
	{
		SetMovePrg();
	}
}

void EnemyMove::MoveLR(void)
{

}
