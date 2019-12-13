#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <Vector2.h>

#define PI 3.141592						// 円周率

enum class STATE
{
	NORMAL,			// 通常
	EX,				// 特殊状態
	DETH,			// 爆発 (死亡)
	MAX
};

// 
enum class UNIT_ID
{
	NON,
	PLAYER,
	ENEMY,
	PL_BULLET,
	EM_BULLET
};

class Obj;			// ﾌﾟﾛﾄﾀｲﾌﾟｾﾝｹﾞﾝてきな
using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual void Update(sharedObj obj) = 0;
	virtual void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const STATE state);								// ｱﾆﾒｷｰの設定

	// ほしいものを返すだけ
	const STATE state(void) const;								
	const Vector2dbl &pos(void) const;
	const Vector2dbl &size(void) const;
	const UNIT_ID &unitID(void) const;
	const bool &exFlag(void) const;

	// ｾｯﾄ
	bool SetAttack(bool exflag);								// 攻撃ﾌﾗｸﾞのセット
	bool SetAnim(const STATE state, AnimVector& data);			// ｱﾆﾒｰｼｮﾝdataの登録
	virtual bool SetAlive(bool alive);
	bool isAlive(void) { return _alive; }						// 状態を取得するためだけ
	bool isDead(void) { return _dead; }
	bool isAnimEnd(void);										// ｱﾆﾒｰｼｮﾝ修了確認
private:


protected:
	bool DestroyPrpc(void);
	bool _alive;												// 生きているか
	bool _dead;													// 死んでいるか
	Vector2dbl _pos;											// 座標
	Vector2dbl _size;											// 画像ｻｲｽﾞ
	double _rad;												// 角度
	int _zOder;													// 描画の優先
	UNIT_ID _unitID;											// 識別用
	bool _exFlag;												// 攻撃ﾌﾗｸﾞ

	std::map<STATE, AnimVector> _animMap;						// ｱﾆﾒｰｼｮﾝ格納
	STATE _state;												// 状態
	unsigned int _animFrame;									// ｱﾆﾒｰｼｮﾝ用ﾌﾚｰﾑ
	unsigned int _animCount;									// ｱﾆﾒｰｼｮﾝ用ｶｳﾝﾄ
};

