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
	modeKeyOld = 1;													// 
	key = 0;

	func = &KeyState::RefKeyData;									// ���O��Ԃ������Ă����Ăǂ�class�̱��ڽ�����ǂ点�Ă�����
}

KeyState::~KeyState()
{

}

void KeyState::Update(void)
{
	SetOld();														// new �� old�@�ɏ���
	modeKeyOld = _buf[KEY_INPUT_F1];
	GetHitKeyStateAll(_buf);										// �S�Ă̷������擾
	(this->*func)();												// this �������g
}

void KeyState::RefKeyData(void)
{
	for (auto id : INPUT_ID())										// now�̃Z�b�g
	{
		state(id, static_cast<int>(_buf[_keyCon[static_cast<int>(id)]]));
	}
	
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)							// ��̨�ސ؂�ւ�
	{
		func = &KeyState::SetKeyConfing;
		TRACE("����̨�ދN��\n");
	}
}

void KeyState::SetKeyConfing(void)
{

	for (int id = 0; id < 256; id++)
	{
		bool flag = false;

		if (_buf[id])
		{
			for (int i = 0; i < key; i++)
			{
				if (_keyCon[i] == id )
				{
					flag = true;
				}
			}

			if (!flag)
			{
				_keyCon[key] = id;
				TRACE("%d\n", key);
				key++;
			}
		}

		if (key == static_cast<int>(end(INPUT_ID())))
		{
			key = 0;
			TRACE("reset\n");
			func = &KeyState::RefKeyData;							// ���O��Ԃ������Ă����Ăǂ�class�̱��ڽ�����ǂ点�Ă�����
			TRACE("����̨�ޏI��\n");
		}
	}

	if (_buf[KEY_INPUT_F1] && !modeKeyOld)							// ��̨�ސ؂�ւ�
	{
		func = &KeyState::RefKeyData;								// ���O��Ԃ������Ă����Ăǂ�class�̱��ڽ�����ǂ点�Ă�����
		TRACE("����̨�ޏI��\n");
	}
}
