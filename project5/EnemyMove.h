#pragma once
#include <Vector2.h>
#include <vector>

enum class MOVE_TYPE
{
	WAIT,
	SIGMOID,
	SPIRAL,
	PITIN,
	LR,
};

										// 動き	 ,	目的地	を格納する
using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2dbl>>;

class EnemyMove
{
public:
	EnemyMove(Vector2dbl& pos );
	~EnemyMove();
	void Update(void);										// 更新
	bool SetMoveState(MoveState& state, bool newFlag);		// 新しい情報が欲しくなった時用フラグ

private:
	void SetMovePrg(void);									// _aimの中の情報をｾｯﾄする

	// ﾒﾝﾊﾞｰ関数ﾎﾟｲﾝﾀｰ
	void (EnemyMove::*_move)(void);							// ﾒﾝﾊﾞｰ関数ﾎﾟｲﾝﾀｰ格納用
	void MoveSigmoid(void);									// ｼｸﾞﾓｲﾄﾞ曲線用
	void MoveSpiral(void);									// ｽﾊﾟｲﾗﾙ
	void PitIn(void);										// 配置
	void Wait(void);										// 待ち時間
	void MoveLR(void);										// 右と左

	int count;

	MoveState _aim;											// 目標に関する情報格納
	int _aimCnt;											// 敵の管理用
	
	Vector2dbl _startPos;									// 各移動関数のｽﾀｰﾄ地点
	Vector2dbl _endPos;										// 各移動関数のｴﾝﾄﾞ地点

	Vector2dbl& _pos;										// 座標
};

