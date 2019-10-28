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

	if (fopen_s(&fp, "data/key.dat", "r") == 0)
	{
		_keyCon.resize(8);
		TRACE("�ǂݍ��񂾷���ݒ肵�܂��B\n");
		fread(&_keyCon[0], sizeof(int), _keyCon.size(), fp);	// ̧�ق̓ǂݍ���
		fclose(fp);												// ���܂�
	}
	else
	{	
		TRACE("��̫�ķ���ݒ肵�܂��B\n");
		// ̧�قɉ����Ȃ���������̫�ľ�ò
		_keyCon = _keyConDef;
	}

	modeKeyOld = 1;													// 

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
		_confID = begin(INPUT_ID());
		func = &KeyState::SetKeyConfing;
		TRACE("����̨�ދN��\n");
	}
}

void KeyState::SetKeyConfing(void)
{

	if (_buf[KEY_INPUT_F1] && !modeKeyOld)						// ��̨�ސ؂�ւ�
	{
		func = &KeyState::RefKeyData;							// ���O��Ԃ������Ă����Ăǂ�class�̱��ڽ�����ǂ点�Ă�����
		TRACE("����̨�ޏI��\n");
		return;
	}

	// ���ގ��œ��������ݒ肳��Ă��邩
	auto checkKey = [&](int id)
	{
		for (auto ckId = begin(INPUT_ID()); ckId < _confID; ++ckId)
		{
			if (_keyCon[static_cast<int>(ckId)] == id)			// ID ����
			{
				return false;
			}
		}
		return true;
	};

	for (int id = 0; id < sizeof(_buf); id++)
	{
		if (!checkKey(id))										// �����Ƃ���
		{
			continue;											// �������for����Ă�
		}

		if (_buf[id] && !_buf[KEY_INPUT_F1])
		{
			_keyCon[static_cast<int>(_confID)] = id;
			++_confID;											// �O���Z����Ȃ��Ɖ���++���邩�킩���Ă���Ȃ�

			if (_confID >= end(_confID))						// �ݒ肪�S������������I������
			{
				if (fopen_s(&fp, "data/key.dat", "w") == 0)
				{
					// ̧�قւ̏�������
					fwrite(&_keyCon[0], sizeof(int), _keyCon.size(), fp);
					fclose(fp);									// ���܂�

					TRACE("����̨�ޏI��\n");
					func = &KeyState::RefKeyData;				// ���O��Ԃ������Ă����Ăǂ�class�̱��ڽ�����ǂ点�Ă�����
					break;
				}
				else
				{
					AST();
				}
			}

			TRACE("%d/%d�Ԗڂ̷��ݒ�\n",
				static_cast<int>(_confID),
				end(INPUT_ID())
			);
		}
	}
}
