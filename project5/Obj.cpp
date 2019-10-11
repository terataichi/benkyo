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
	if (_animMap.find(_state) == _animMap.end())
	{
		return;
	}
	// ����ڰт̒l���͈͓����ǂ���
	if (_animMap[_state].size() <= _animFrame || 0 > _animFrame)
	{
		return;
	}

	
	if (_animMap[_state][_animFrame].first >= 0)
	{
		// ϯ�߂̒��̐ݒ肵�����ĂƱ�Ѷ��Ă��ׂ�
		if (_animMap[_state][_animFrame].second <= _animCount)
		{
			_animFrame++;
		}

		_animCount++;	// ����++

		// �Ō�܂ű�Ұ��݂�����ؾ��
		if (_animMap[_state].size() <= _animFrame)
		{
			_animFrame = 0;
			_animCount = 0;
		}
	}

	// �`��
	lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,_pos.x,_pos.y });
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id,_pos.x,_pos.y });
}

Obj::~Obj()
{
}

bool Obj::state(const STATE state)
{
	// ���ʂȷ��ޱٶ������
	if (_animMap.find(state) == _animMap.end())
	{
		return false;
	}

	// �؂�ւ���Ƃ���ؾ�Ă���
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

bool Obj::SetAnim(const STATE state, AnimVector& data)
{
	//// �󂯎�����ް����i�[
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	_animMap[key] = data;
	//	return true;
	//}
	//return false;

	// C++ 17�ȍ~���������s�ł�����
	return (_animMap.try_emplace(state, std::move(data))).second;
}

// �����m�F
bool Obj::SetAlive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		state(STATE::DETH);
	}

	return true;
}

// ��Ұ��ݏI������
bool Obj::isAnimEnd(void)
{
	// ���ϯ�߂̒��ɷ��������Ɠ����Ă邩��������
	if (_animMap.find(_state) == _animMap.end())
	{
		return true;
	}

	// ����ڰт̒l���͈͓����ǂ���
	if (_animMap[_state].size() <= _animFrame || 0 > _animFrame)
	{
		return true;
	}

	// �������I����Ă����玀��ł��炢����
	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	return false;
}
