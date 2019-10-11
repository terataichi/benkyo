#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <Vector2.h>

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
	void Update(void);
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const STATE state);								// ｱﾆﾒｷｰの設定
	const STATE state(void) const;								// 返すよ

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
	bool _alive;												// 生きているか
	bool _dead;													// 死んでいるか
	Vector2 _pos;												// 座標
	Vector2 _size;												// 画像ｻｲｽﾞ
};

