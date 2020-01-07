#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <Vector2.h>
#include "DIR.h"

#define PI 3.141592						// 円周率
#define BLOCK_SIZE 16

enum class ANIMSTATE
{
	NORMAL,			// 通常
	DETH,			// (死亡)
	MAX
};

class Obj;			// ﾌﾟﾛﾄﾀｲﾌﾟｾﾝｹﾞﾝてきな
using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;
using BlockMap = std::map < DIR, std::vector<std::vector<int>>>;

class Obj
{
public:
	Obj();
	virtual void Update() = 0;
	virtual void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const ANIMSTATE state);								// ｱﾆﾒｷｰの設定

	// ほしいものを返すだけ
	const ANIMSTATE state(void) const;								
	const Vector2 &pos(void) const;
	const Vector2 &size(void) const;
	const BlockMap &blockData(void) const;
	const DIR &dir(void) const;

	// ｾｯﾄ
	bool SetAnim(const ANIMSTATE state, AnimVector& data);			// ｱﾆﾒｰｼｮﾝdataの登録
	virtual bool SetAlive(bool alive);
	bool SetState(ANIMSTATE state);
	bool SetBlock(BlockMap data);								// ﾌﾞﾛｯｸの内容を書き換えるときに使う
	bool isAlive(void) { return _alive; }						// 状態を取得するためだけ
	bool isDead(void) { return _dead; }
	bool isAnimEnd(void);										// ｱﾆﾒｰｼｮﾝ修了確認
protected:
	bool _moveFlg;												// 操作してるやつﾌﾗｸﾞ

	bool DestroyPrpc(void);
	bool _alive;												// 生きているか
	bool _dead;													// 死んでいるか
	Vector2 _pos;												// 座標
	Vector2 _size;												// 画像ｻｲｽﾞ
	Vector2 _upLeft;											// ﾚｸﾄｸﾞﾗﾌの左上の座標
	double _rad;												// 角度
	int _zOder;													// 描画の優先

	std::map<ANIMSTATE, AnimVector> _animMap;						// ｱﾆﾒｰｼｮﾝ格納
	ANIMSTATE _state;												// 状態
	unsigned int _animFrame;									// ｱﾆﾒｰｼｮﾝ用ﾌﾚｰﾑ
	unsigned int _animCount;									// ｱﾆﾒｰｼｮﾝ用ｶｳﾝﾄ
	BlockMap _blockData;	// ﾌﾞﾛｯｸのﾃﾞｰﾀ格納用
	DIR _dir;													// ﾌﾞﾛｯｸの向き
};

