#include <DxLib.h>
#include <Scene\SceneMng.h>
#include <ImageMng.h>
#include "Obj.h"



Obj::Obj()
{
	_animFrame = 0;
	_animCount = 0;
}

void Obj::Update(void)
{

}

void Obj::Draw(void)
{
	// ｱﾆﾑﾏｯﾌﾟの中にｷｰがちゃんと入ってるかﾁｪｯｸする
	if (_animMap.find(_animKey) == _animMap.end())
	{
		return;
	}

	// ｱﾆﾑﾌﾚｰﾑの値が範囲内かどうか
	if (_animMap[_animKey].size() <= _animFrame || 0 > _animFrame)
	{
		return;
	}

	_animCount++;

	// ﾏｯﾌﾟの中の設定ｶｳﾝﾄとｱﾆﾑｶｳﾝﾄを比べる
	if (_animMap[_animKey][_animFrame].second <= _animCount)
	{
		_animFrame++;

		if (_animMap[_animKey].size() <= _animFrame)
		{
			_animFrame = 0;
			_animCount = 0;
		}
	}

	// 描画
	lpSceneMng.AddDrawQue({ _animMap[_animKey][_animFrame].first,_pos.x,_pos.y });
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id,_pos.x,_pos.y });
}

Obj::~Obj()
{
}

bool Obj::animKey(const std::string key)
{
	// 無駄なｷｰｶﾞｱﾙｶﾁｪｯｸｽﾙ
	if (_animMap.find(key) == _animMap.end())
	{
		return false;
	}

	// 切り替えるときにﾘｾｯﾄする
	if (_animKey != key)
	{
		_animFrame = 0;
		_animCount = 0;
	}

	_animKey = key;
	return true;
}

const std::string Obj::animKey(void) const
{
	return _animKey;
}

bool Obj::SetAnim(const std::string key, AnimVector& data)
{
	//// 受け取ったﾃﾞｰﾀを格納
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	_animMap[key] = data;
	//	return true;
	//}
	//return false;

	// C++ 17以降だったら一行でかける
	return (_animMap.try_emplace(key, std::move(data))).second;
}
