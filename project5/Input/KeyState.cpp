#include <DxLib.h>
#include <_DebugConOut.h>
#include "KeyState.h"
#include "InputState.h"



KeyState::KeyState()
{
	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));		// ���̕ۑ��̈�̗\�������
	
	_keyConDef.emplace_back(KEY_INPUT_LEFT);
	_keyConDef.emplace_back(KEY_INPUT_RIGHT);
	_keyConDef.emplace_back(KEY_INPUT_UP);
	_keyConDef.emplace_back(KEY_INPUT_DOWN);
	_keyConDef.emplace_back(KEY_INPUT_Z);
	_keyConDef.emplace_back(KEY_INPUT_X);
	_keyConDef.emplace_back(KEY_INPUT_A);
	_keyConDef.emplace_back(KEY_INPUT_S);

	_keyCon = _keyConDef;											// ���e���߰����

	func = &KeyState::RefKeyData;									// ���O��Ԃ������Ă����Ăǂ�class�̱��ڽ�����ǂ点�Ă�����
}


KeyState::~KeyState()
{

}

void KeyState::Update(void)
{
	SetOld();														// new �� old�@�ɏ���
	GetHitKeyStateAll(_buf);										// �S�Ă̷������擾
	(this->*func)();												// this �������g
}

void KeyState::RefKeyData(void)
{
	for (auto id : INPUT_ID())
	{
		state(id, static_cast<int>(_buf[_keyCon[static_cast<int>(id)]]));
	}
	
	if (_buf[KEY_INPUT_F1])
	{
		func = &KeyState::SetKeyConfing;
		TRACE("SetKeyConfing\n");
	}
}

void KeyState::SetKeyConfing(void)
{
	if (_buf[KEY_INPUT_F1])
	{
		func = &KeyState::RefKeyData;									// ���O��Ԃ������Ă����Ăǂ�class�̱��ڽ�����ǂ点�Ă�����
		TRACE("RefKeyData\n");
	}
}
