#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <Vector2.h>

enum class STATE
{
	NORMAL,			// 通常
	DETH,			// 死亡
	MAX
};

class Obj;			// ﾌﾟﾛﾄﾀｲﾌﾟｾﾝｹﾞﾝてきな
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual void Update(void) = 0;
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

private:
	STATE _state;												// 状態
	unsigned int _animFrame;									// ｱﾆﾒｰｼｮﾝ用ﾌﾚｰﾑ
	unsigned int _animCount;									// ｱﾆﾒｰｼｮﾝ用ｶｳﾝﾄ

protected:
	//bool DestroyPrpc(void);
	bool _alive;												// 生きているか
	bool _dead;													// 死んでいるか
	Vector2 _pos;												// 座標
	Vector2 _size;												// 画像ｻｲｽﾞ
	Vector2 _rect;												// 画像の左上座標
};

