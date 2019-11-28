#include <DxLib.h>
#include <Scene\SceneMng.h>
#include <ImageMng.h>
#include "Obj.h"



Obj::Obj()
{
	// 初期化
	_exFlag = false;
	_alive = true;
	_dead = false;
	_animFrame = 0;
	_animCount = 0;
	_rad = 0;
	_unitID = UNIT_ID::NON;
	_zOder = 50000;
}

void Obj::Draw(void)
{
	// ｱﾆﾑﾏｯﾌﾟの中にｷｰがちゃんと入ってるかﾁｪｯｸする
	if (_animMap.find(_state) == _animMap.end())
	{
		return;
	}
	// ｱﾆﾑﾌﾚｰﾑの値が範囲内かどうか
	if (_animMap[_state].size() <= _animFrame || 0 > _animFrame)
	{
		return;
	}

	
	if (_animMap[_state][_animFrame].first >= 0)
	{
		// ﾏｯﾌﾟの中の設定したｶｳﾝﾄとｱﾆﾑｶｳﾝﾄを比べる
		if (_animMap[_state][_animFrame].second <= _animCount)
		{
			_animFrame++;
		}

		_animCount++;	// ｶｳﾝﾄ++

		// 最後までｱﾆﾒｰｼｮﾝしたらﾘｾｯﾄ
		if (_animMap[_state].size() <= _animFrame)
		{
			_animFrame = 0;
			_animCount = 0;
		}
	}

	// 描画
	lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,lpSceneMng.GameScreenOffset.x + _pos.x,lpSceneMng.GameScreenOffset.y + _pos.y ,_rad , _zOder, LAYER::CHAR });
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id,lpSceneMng.GameScreenOffset.x + _pos.x,lpSceneMng.GameScreenOffset.y + _pos.y ,_rad, _zOder, LAYER::CHAR });
}

Obj::~Obj()
{
}

bool Obj::state(const STATE state)
{
	// 無駄なｷｰｶﾞｱﾙｶﾁｪｯｸｽﾙ
	if (_animMap.find(state) == _animMap.end())
	{
		return false;
	}

	// 切り替えるときにﾘｾｯﾄする
	if (_state != state)
	{
		_animFrame = 0;
		_animCount = 0;
	}

	_state = state;
	return true;
}

const STATE Obj::state(void) const
{
	return _state;
}

const Vector2dbl & Obj::pos(void) const
{
	return _pos;
}

const Vector2dbl & Obj::size(void) const
{
	return _size;
}

const UNIT_ID & Obj::unitID(void) const
{
	return _unitID;
}

const bool Obj::exFlag(void) const
{
	return false;
}

bool Obj::SetAttack(bool exflag)
{
	_exFlag = exflag;
	return true;
}

bool Obj::SetAnim(const STATE state, AnimVector& data)
{
	//// 受け取ったﾃﾞｰﾀを格納
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	_animMap[key] = data;
	//	return true;
	//}
	//return false;

	// C++ 17以降だったら一行でかける
	return (_animMap.try_emplace(state, std::move(data))).second;
}

// 生存確認
bool Obj::SetAlive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		state(STATE::DETH);
	}

	return true;
}

// ｱﾆﾒｰｼｮﾝ終了ﾁｪｯｸ
bool Obj::isAnimEnd(void)
{
	// ｱﾆﾑﾏｯﾌﾟの中にｷｰがちゃんと入ってるかﾁｪｯｸする
	if (_animMap.find(_state) == _animMap.end())
	{
		return true;
	}

	// ｱﾆﾑﾌﾚｰﾑの値が範囲内かどうか
	if (_animMap[_state].size() <= _animFrame || 0 > _animFrame)
	{
		return true;
	}

	// 爆発が終わっていたら死んでもらいたい
	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	return false;
}

// 破棄していいかどうか
bool Obj::DestroyPrpc(void)
{
	// 生きてたらﾀﾞﾒ
	if (_alive)
	{
		return false;
	}

	// ｱﾆﾒｰｼｮﾝが終了してたら破棄
	if (isAnimEnd())
	{
		_dead = true;
	}

	return true;
}
