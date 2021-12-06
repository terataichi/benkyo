#include <DxLib.h>
#include "Scene/SceneMng.h"
#include "common/ImageMng.h"
#include "Obj.h"
#include "_Debug/_DebugConOut.h"

Obj::Obj()
{
	// 初期化
	_alive = true;
	_dead = false;
	_animFrame = 0;
	_animCount = 0;
	_rad = 0;
	_zOder = 50000;
	_dir = DIR::UP;
	_moveFlg = true;
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
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if(_blockData[_dir][y][x] != 0)
			lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,
				lpSceneMng.GameScreenOffset.x + _pos.x + BLOCK_SIZE * x,
				lpSceneMng.GameScreenOffset.y + _pos.y + BLOCK_SIZE * y,
				_upLeft.x,
				_upLeft.y,
				_size.x,
				_size.y,
				_zOder,
				LAYER::CHAR });
		}
	}
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id,
							lpSceneMng.GameScreenOffset.x + _pos.x,
							lpSceneMng.GameScreenOffset.y + _pos.y,
							_upLeft.x,
							_upLeft.y,
							_size.x,
							_size.y,
							50000,
							LAYER::CHAR });
}

Obj::~Obj()
{
}

bool Obj::state(const ANIMSTATE state)
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

const ANIMSTATE Obj::state(void) const
{
	return _state;
}

const Vector2 & Obj::pos(void) const
{
	return _pos;
}

const Vector2 & Obj::size(void) const
{
	return _size;
}

const BlockMap & Obj::blockData(void) const
{
	return _blockData;
}

const DIR & Obj::dir(void) const
{
	return _dir;
}

bool Obj::SetAnim(const ANIMSTATE state, AnimVector& data)
{
	// C++ 17以降だったら一行でかける
	return (_animMap.try_emplace(state, std::move(data))).second;
}

// 生存確認
bool Obj::SetAlive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		state(ANIMSTATE::DETH);
	}

	return true;
}

bool Obj::SetState(ANIMSTATE state)
{
	_state = state;

	return true;
}

bool Obj::SetBlock(BlockMap data)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			_blockData[_dir][y][x] = data[_dir][y][x];
		}
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
	if (!_alive)
	{
		_dead = true;
	}

	return true;
}
