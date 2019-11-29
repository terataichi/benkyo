#pragma once
#include <Vector2.h>
#include <vector>
#include "Obj.h"

enum class MOVE_TYPE
{
	WAIT,								// 待ち時間
	SIGMOID,							// ｼｸﾞﾓｲﾄﾞ曲線
	SPIRAL,								// 回転
	PITIN,								// ﾋﾟｯﾄｲﾝ
	LR,									// 左右移動
	SCALE,								// 拡大縮小すけーる
	ATTACK								// 突撃
};

#define LR_GAIN 120						// 左右移動の移動幅

										// 動き	 ,	目的地	を格納する
using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2dbl>>;

class EnemyMove
{
public:
	EnemyMove(Vector2dbl& pos, double& rad, bool& atFlag);
	~EnemyMove();
	const MOVE_TYPE MoveType(void)const;
	void Update(sharedObj obj);								// 更新
	bool SetMoveState(MoveState& state, bool newFlag);		// 新しい情報が欲しくなった時用フラグ
	void PitInCnt(void);									// 敵の処理
	MoveState _aim;											// 目標に関する情報格納

private:
	void SetMovePrg(void);									// _aimの中の情報をｾｯﾄする

	// ﾒﾝﾊﾞｰ関数ﾎﾟｲﾝﾀｰ
	void (EnemyMove::*_move)(void);							// ﾒﾝﾊﾞｰ関数ﾎﾟｲﾝﾀｰ格納用
	void MoveSigmoid(void);									// ｼｸﾞﾓｲﾄﾞ曲線用
	void MoveSpiral(void);									// ｽﾊﾟｲﾗﾙ
	void PitIn(void);										// 配置
	void Wait(void);										// 待ち時間
	void MoveLR(void);										// 左右移動
	void MoveScale(void);									// 拡大縮小
	void MoveAttack(void);									// 突撃

	int _count;												// 待ち時間などのﾌﾚｰﾑ管理用

	int _aimCnt;											// 敵の管理用
	
	Vector2dbl _startPos;									// 各移動関数のｽﾀｰﾄ地点
	Vector2dbl _endPos;										// 各移動関数のｴﾝﾄﾞ地点

	Vector2dbl& _pos;										// 座標を参照で受け取る
	Vector2dbl _oldPos;										// 前のﾌﾚｰﾑにいた座標格納

	double& _rad;											// 角度を参照で受け取って書き換えるための

	double _angle;											// 円描画用の角度
	double _angleTotal;										// 角度の合計値
	double _angleCon;										// 角度制御1か-1をかけてあげる

	Vector2dbl _lenght;										// 自機の角度を変えるよ

	double _radius;											// 半径

	Vector2dbl _oneMoveVec;									// １ﾌﾚｰﾑ当たりの移動量

	double _moveGain;										// ｼｸﾞﾓｲﾄﾞ用の動きの幅

	Vector2dbl _scaleGain;									// 拡大縮小用の幅
	int _scaleCnt;											// ｹﾞｰﾑｶｳﾝﾄだと最初ずれて始まるから新しく作った

	static int _pitInCnt;									// 全員揃ったか確認するための 

	Vector2dbl _plPos;										// ﾌﾟﾚｲﾔｰの座標格納用

	bool& _exFlag;											// ｱﾀｯｸﾌﾗｸﾞ
	
	Vector2dbl _scalePos;									// 攻撃終了後最初のｽﾀｰﾄﾎﾟｽを基準を等倍としてみてほしいから						
};

