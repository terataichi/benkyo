#include <DxLib.h>
#include "Scene/SceneMng.h"
#include "common/ImageMng.h"
#include "Obj.h"
#include "_Debug/_DebugConOut.h"

Obj::Obj()
{
	// ������
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
	// C++ 17�ȍ~���������s�ł�����
	return (_animMap.try_emplace(state, std::move(data))).second;
}

// �����m�F
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
	if (!_alive)
	{
		_dead = true;
	}

	return true;
}
