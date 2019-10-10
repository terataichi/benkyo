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
	// ±ÆÑÏ¯Ìß‚Ì’†‚É·°‚ª‚¿‚á‚ñ‚Æ“ü‚Á‚Ä‚é‚©Áª¯¸‚·‚é
	if (_animMap.find(_animKey) == _animMap.end())
	{
		return;
	}
	// ±ÆÑÌÚ°Ñ‚Ì’l‚ª”ÍˆÍ“à‚©‚Ç‚¤‚©
	if (_animMap[_animKey].size() <= _animFrame || 0 > _animFrame)
	{
		return;
	}

	
	if (_animMap[_animKey][_animFrame].first >= 0)
	{
		// Ï¯Ìß‚Ì’†‚Ìİ’è‚µ‚½¶³İÄ‚Æ±ÆÑ¶³İÄ‚ğ”ä‚×‚é
		if (_animMap[_animKey][_animFrame].second <= _animCount)
		{
			_animFrame++;
		}

		_animCount++;	// ¶³İÄ++

		// ÅŒã‚Ü‚Å±ÆÒ°¼®İ‚µ‚½‚çØ¾¯Ä
		if (_animMap[_animKey].size() <= _animFrame)
		{
			_animFrame = 0;
			_animCount = 0;
		}
	}

	// •`‰æ
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
	// –³‘Ê‚È·°¶Ş±Ù¶Áª¯¸½Ù
	if (_animMap.find(key) == _animMap.end())
	{
		return false;
	}

	// Ø‚è‘Ö‚¦‚é‚Æ‚«‚ÉØ¾¯Ä‚·‚é
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
	//// ó‚¯æ‚Á‚½ÃŞ°À‚ğŠi”[
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	_animMap[key] = data;
	//	return true;
	//}
	//return false;

	// C++ 17ˆÈ~‚¾‚Á‚½‚çˆês‚Å‚©‚¯‚é
	return (_animMap.try_emplace(key, std::move(data))).second;
}
