#include "EnemyMove.h"
#include <algorithm>
#include <math.h>
#include <Vector2.h>
#include <Enemy.h>
#include "_Debug/_DebugConOut.h"
#include "_Debug/_DebugDispOut.h"
#include <Scene\SceneMng.h>

int EnemyMove::_pitInCnt;

EnemyMove::EnemyMove(Vector2dbl& pos, double& rad) :_pos(pos),_rad(rad)
{
	_move = nullptr;
	_aimCnt = -1;						// 0だといきなりｱｸｾｽする
	_angleTotal = std::atan(0.0);		// 0度を格納
	_pitInCnt = 0;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(sharedObj obj)
{
	_plPos = (*obj).pos();
	if (_move != nullptr)					// 中身があるかないかチェックする
	{
		(this->*_move)();					// 優先度をつけるためにかっこをつけないといけない
											// つけないとthis->(*_move())なってしまう。
	}

	// ﾃﾞﾊﾞｯｸﾞ用
	//_dbgDrawPixel(lpSceneMng.GameScreenOffset.x +  _pos.x, lpSceneMng.GameScreenOffset.y + _pos.y, 0xffffff);
	//_dbgDrawBox(lpSceneMng.GameScreenOffset.x + _pos.x - 15, lpSceneMng.GameScreenOffset.y + _pos.y - 15, lpSceneMng.GameScreenOffset.x + _pos.x + 15, lpSceneMng.GameScreenOffset.y +_pos.y + 15, 0xffffff, false);
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

void EnemyMove::PitInCnt(void)
{
	_pitInCnt++;
}

void EnemyMove::SetMovePrg(void)
{
	
	_aimCnt++;


	if (_aimCnt >= static_cast<int>(_aim.size()))
	{
		auto checkAim = [&]() {
			for (_aimCnt = 0; _aimCnt < _aim.size(); _aimCnt++)
			{
				if (_aim[_aimCnt].first == MOVE_TYPE::SCALE)
				{
					return true;
				}
			}
			return false;
		};

		if (!checkAim())
		{
			return;
		}
	}

	// アタックし終わったら上に戻ってねー
	if (_pos.y >= lpSceneMng.GameScreenSize.y)
	{
		_pos.y = -100;
	}

	_startPos = _pos;					// 今の位置がｽﾀｰﾄ地点
	_endPos = _aim[_aimCnt].second;		// 最終地点

	// firstの中のTYPEによって動き方を変える
	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		count = 0;
		_move = &EnemyMove::Wait;
		break;
	case MOVE_TYPE::SIGMOID:
		_moveGain = -5;																				// ｼｸﾞﾓｲﾄﾞを上から始めるために-10を入れた
		_oneMoveVec.x = ((_endPos.x - _startPos.x) / 90.0);											// 3秒経つまでに移動させる１ﾌﾚｰﾑの移動量
		_move = &EnemyMove::MoveSigmoid;
		break;
	case MOVE_TYPE::SPIRAL:
		_angle = std::atan( _startPos.y - _endPos.y );													// 初期の角度をきめる
		_radius = abs(_endPos.y - _startPos.y);															// 半径の設定
		_angleCon = (((_endPos.y - _startPos.y) / abs(_endPos.y - _startPos.y)) *(((lpSceneMng.ScreenCenter.x / 2 - _startPos.x) / abs(lpSceneMng.ScreenCenter.x / 2 - _startPos.x))) * -1);
		_move = &EnemyMove::MoveSpiral;
		break;
	case MOVE_TYPE::PITIN:
		count = 0;
		// ｱｯﾀｸが終わったら通常の処理にも
		if (_startPos.y > 0)
		{
			_endPos.x = ((_endPos.x - 60) + (((lpSceneMng._gameCount + 60) / LR_GAIN) % 2 * LR_GAIN)) + (((lpSceneMng._gameCount + 60) % LR_GAIN) * ((((lpSceneMng._gameCount + 60) / LR_GAIN) % 2) * -2 + 1));
		}
		_oneMoveVec = ((_endPos - _startPos) / 60.0);													// 2秒経つまでに移動させる１ﾌﾚｰﾑの移動量
		_move = &EnemyMove::PitIn;
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		break;
	case MOVE_TYPE::SCALE:
		_scaleCnt = 30;		// 拡大率0で始めたいから30をいれた
		_scaleGain = (_endPos - _startPos);
		count = 0;
		_move = &EnemyMove::MoveScale;
		break;
	case MOVE_TYPE::ATTACK:
		_move = &EnemyMove::MoveAttack;
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
		_moveGain += 0.12;
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
	if (_angleTotal < ((PI * (45 * 9)) / 180.0))
	{
		// 一番最初に前ﾌﾚｰﾑにいた座標を格納する
		_oldPos = _pos;

		// 移動
		_pos.x = (_radius * std::cos(_angle)) + _endPos.x;
		_pos.y = (_radius * std::sin(_angle)) + _endPos.y;

		// 角度制御							
		_angle += (PI * 3) / 120.0 * _angleCon;
		_angleTotal += (PI * 3) / 120.0;			// 合計加算

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
	
	if (count < 60)								// XかYだけをﾁｪｯｸすることによって計算量が減る
	{
		// 移動量が残っている場合
		_pos += _oneMoveVec;

		// 角度の処理
		_lenght = _endPos - _pos;													// 原点に合わせる
		_rad = std::atan2(_lenght.y, _lenght.x) + (PI * 90.0 )/ 180.0;				// 角度を測る
		//_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90.0);
		//_rad = std::atan2(-_pos.x + _endPos.x, -_endPos.y + _pos.y);
	}
	else
	{
		// 格納し終わったら切り替える
		_pos = _endPos;																// 一応ずれを修正する
		_rad = 0;																	// 動き終わったら角度をもとの位置に戻す
		_pitInCnt++;
		SetMovePrg();
	}
	count++;
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

	// 左右移動
	_pos.x = ((_endPos.x - 60) + ((lpSceneMng._gameCount / LR_GAIN) % 2 * LR_GAIN)) + ((lpSceneMng._gameCount % LR_GAIN) * (((lpSceneMng._gameCount / LR_GAIN) % 2) * -2 + 1));

	// 最後尾の奴までそろって　かつ　ｴﾝﾄﾞﾎﾟｽにいたら
	if (_pitInCnt >= ENEMY_MAX && (_endPos.x / 100.0) == (_pos.x / 100.0))
	{
		SetMovePrg();
	}
}

void EnemyMove::MoveScale(void)
{
	// デバック用
	//_dbgDrawLine(lpSceneMng.GameScreenOffset.x + _startPos.x, 0, lpSceneMng.GameScreenOffset.x + _startPos.x, lpSceneMng.ScreenSize.y, 0xfffff);
	
	_scaleCnt++;
	count++;
	// 移動
	_pos =
			_startPos +
			_scaleGain *
			(static_cast<double>(((_scaleCnt + 100) / 2) % 30 ) / 100.0) *
			((static_cast<double>((((_scaleCnt + 100) / 2) / 30) % 2) * -2.0 + 1.0) * -1) -
			(static_cast<double>((((_scaleCnt + 100) / 2) / 30) % 2) * (_scaleGain * 0.3));

	if (count >= 180)
	{
		SetMovePrg();
	}
}

void EnemyMove::MoveAttack(void)
{

	_endPos = { _plPos.x , _plPos.y + 100.0 };														// ﾌﾟﾚｲﾔｰより少し下を目標地点にする
	_move = &EnemyMove::PitIn;
	count = 0;
	_oneMoveVec = ((_endPos - _startPos) / 60.0);													// 2秒経つまでに移動させる１ﾌﾚｰﾑの移動量
}
