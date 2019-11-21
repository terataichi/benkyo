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

class Obj;			// ﾌﾟﾛﾄﾀｲﾌﾟｾﾝｹﾞﾝてきな
using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual void Update(void) = 0;
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const STATE state);								// ｱﾆﾒｷｰの設定
	const STATE state(void) const;								// 返すよ
	const Vector2dbl &pos(void) const;
	const Vector2dbl &size(void) const;


	bool SetAnim(const STATE state, AnimVector& data);			// ｱﾆﾒｰｼｮﾝdataの登録

	bool SetAlive(bool alive);
	bool isAlive(void) { return _alive; }						// 状態を取得するためだけ
	bool isDead(void) { return _dead; }
	bool isAnimEnd(void);										// ｱﾆﾒｰｼｮﾝ修了確認
private:
	std::map<STATE, AnimVector> _animMap;						// ｱﾆﾒｰｼｮﾝ格納
	STATE _state;												// 状態
	unsigned int _animFrame;									// ｱﾆﾒｰｼｮﾝ用ﾌﾚｰﾑ
	unsigned int _animCount;									// ｱﾆﾒｰｼｮﾝ用ｶｳﾝﾄ

protected:
	bool DestroyPrpc(void);
	bool _alive;												// 生きているか
	bool _dead;													// 死んでいるか
	Vector2dbl _pos;											// 座標
	Vector2dbl _size;											// 画像ｻｲｽﾞ
	double _rad;												// 角度
	int _zOder;													// 描画の優先
};

