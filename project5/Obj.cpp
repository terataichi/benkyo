#include <DxLib.h>
#include <Scene\SceneMng.h>
#include <ImageMng.h>
#include "Obj.h"



Obj::Obj()
{
	// ������
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

// �j�����Ă������ǂ���
bool Obj::DestroyPrpc(void)
{
	// �����Ă������
	if (_alive)
	{
		return false;
	}

	// ��Ұ��݂��I�����Ă���j��
	if (isAnimEnd())
	{
		_dead = true;
	}

	return true;
}
