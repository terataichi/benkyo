#include "EnemyMove.h"
#include <math.h>
#include <Vector2.h>
#include "_Debug/_DebugConOut.h"
#include "_Debug/_DebugDispOut.h"
#include <Scene\SceneMng.h>

EnemyMove::EnemyMove(Vector2dbl& pos, double& rad) :_pos(pos),_rad(rad)
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

	// ﾃﾞﾊﾞｯｸﾞ用
	_dbgDrawPixel(lpSceneMng.GameScreenOffset.x +  _pos.x, lpSceneMng.GameScreenOffset.y + _pos.y, 0xffffff);
	_dbgDrawLine(lpSceneMng.ScreenCenter.x, 0 ,lpSceneMng.ScreenCenter.x, lpSceneMng.ScreenSize.y, 0xfffff);
	//_dbgDrawBox(_pos.x - 15, _pos.y - 15, _pos.x + 15, _pos.y + 15, 0xffffff, false);
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
	if (_aimCnt >= static_cast<int>(_aim.size()))
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
		_moveGain = -10;																				// ｼｸﾞﾓｲﾄﾞを上から始めるために-10を入れた
		_oneMoveVec.x = ((_endPos.x - _startPos.x) / 180.0);											// 3秒経つまでに移動させる１ﾌﾚｰﾑの移動量
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		_angle = std::atan( _startPos.y - _endPos.y );													// 初期の角度をきめる
		_radius = abs(_endPos.y - _startPos.y);															// 半径の設定
		_angleCon = (((_endPos.y - _startPos.y) / abs(_endPos.y - _startPos.y)) *(((lpSceneMng.ScreenCenter.x / 2 - _startPos.x) / abs(lpSceneMng.ScreenCenter.x / 2 - _startPos.x))) * -1);
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		_oneMoveVec = ((_endPos - _startPos) / 120.0);													// 2秒経つまでに移動させる１ﾌﾚｰﾑの移動量
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
	// 最終地点の場所かﾁｪｯｸ
	if (abs(_endPos.x - _pos.x) >= abs(_oneMoveVec.x))
	{
		// 一番最初に前ﾌﾚｰﾑにいた座標を格納する
		_oldPos = _pos;

		// ｼｸﾞﾓｲﾄﾞ関数
		_pos.y = ((1.0 / (1.0 + exp(-_moveGain))) * (_endPos.y - _startPos.y)) + _startPos.y;

		// X移動
		_pos.x += _oneMoveVec.x;

		// 今の座標と前の座標で角度を計算する
		_lenght = _pos - _oldPos;
		_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90);

		// 幅を変える
		_moveGain += 0.1;
	}
	else
	{
		_pos = _endPos;																// 一応ずれを修正する
		SetMovePrg();
	}
}

void EnemyMove::MoveSpiral(void)
{

	// 終了条件
	if (_radius >= 0)
	{
		// 一番最初に前ﾌﾚｰﾑにいた座標を格納する
		_oldPos = _pos;


		// 移動
		_pos.x = (_radius * std::cos(_angle)) + _endPos.x;
		_pos.y = (_radius * std::sin(_angle)) + _endPos.y;

		// 角度制御							
		_angle += std::atan(0.03) * _angleCon;

		// 半径小さくする
		_radius -= 0.2;

		// 今の座標と前の座標で角度を計算する
		_lenght = _pos - _oldPos;
		_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90);

	}
	else
	{
		SetMovePrg();
	}

}

void EnemyMove::PitIn(void)
{
	
	if (abs(_endPos - _pos) >= abs(_oneMoveVec))								// XかYだけをﾁｪｯｸすることによって計算量が減る
	{
		// 移動量が残っている場合
		_pos += _oneMoveVec;

		// 角度の処理
		_lenght = _endPos - _pos;													// 原点に合わせる
		_rad = std::atan2(_lenght.y, _lenght.x) + (3.141592 * 90.0 )/ 180.0;		// 角度を測る
		//_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90.0);
		//_rad = std::atan2(-_pos.x + _endPos.x, -_endPos.y + _pos.y);
	}
	else
	{
		// 格納し終わったら切り替える
		_pos = _endPos;																// 一応ずれを修正する
		_rad = 0;																	// 動き終わったら角度をもとの位置に戻す
		SetMovePrg();
	}
}

void EnemyMove::Wait(void)
{
	// 終端地点に来たら切り替える
	if (count > _aim[_aimCnt].second.x)
	{
		SetMovePrg();
	}
	count++;
}

void EnemyMove::MoveLR(void)
{
	// 一番最初に前ﾌﾚｰﾑにいた座標を格納する
	_oldPos = _pos;

	_pos.x -= 5;
	// 今の座標と前の座標で角度を計算する
	_lenght = _pos - _oldPos;
	_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90);

	
}
