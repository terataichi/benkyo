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
	// ���ϯ�߂̒��ɷ��������Ɠ����Ă邩��������
	if (_animMap.find(_animKey) == _animMap.end())
	{
		return;
	}
	// ����ڰт̒l���͈͓����ǂ���
	if (_animMap[_animKey].size() <= _animFrame || 0 > _animFrame)
	{
		return;
	}

	
	if (_animMap[_animKey][_animFrame].first >= 0)
	{
		// ϯ�߂̒��̐ݒ肵�����ĂƱ�Ѷ��Ă��ׂ�
		if (_animMap[_animKey][_animFrame].second <= _animCount)
		{
			_animFrame++;
		}

		_animCount++;	// ����++

		// �Ō�܂ű�Ұ��݂�����ؾ��
		if (_animMap[_animKey].size() <= _animFrame)
		{
			_animFrame = 0;
			_animCount = 0;
		}
	}

	// �`��
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
	// ���ʂȷ��ޱٶ������
	if (_animMap.find(key) == _animMap.end())
	{
		return false;
	}

	// �؂�ւ���Ƃ���ؾ�Ă���
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
	//// �󂯎�����ް����i�[
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	_animMap[key] = data;
	//	return true;
	//}
	//return false;

	// C++ 17�ȍ~���������s�ł�����
	return (_animMap.try_emplace(key, std::move(data))).second;
}
