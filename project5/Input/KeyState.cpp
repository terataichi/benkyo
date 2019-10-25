#include <DxLib.h>
#include <_DebugConOut.h>
#include "KeyState.h"
#include "InputState.h"


KeyState::KeyState()
{
	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));		// ｷｰの保存領域の予約をする
	
	_keyConDef.emplace_back(KEY_INPUT_LEFT);
	_keyConDef.emplace_back(KEY_INPUT_RIGHT);
	_keyConDef.emplace_back(KEY_INPUT_UP);
	_keyConDef.emplace_back(KEY_INPUT_DOWN);
	_keyConDef.emplace_back(KEY_INPUT_Z);
	_keyConDef.emplace_back(KEY_INPUT_X);
	_keyConDef.emplace_back(KEY_INPUT_A);
	_keyConDef.emplace_back(KEY_INPUT_S);

	_keyCon = _keyConDef;											// 内容をｺﾋﾟｰする
	modeKeyOld = 1;													// 
	key = 0;

	func = &KeyState::RefKeyData;									// 名前空間を書いてあげてどのclassのｱﾄﾞﾚｽかたどらせてあげる
}

KeyState::~KeyState()
{

}

void KeyState::Update(void)
{
	SetOld();														// new を old　に書く
	modeKeyOld = _buf[KEY_INPUT_F1];
	GetHitKeyStateAll(_buf);										// 全てのｷｰ情報を取得
	(this->*func)();												// this 自分自身
}

void KeyState::RefKeyData(void)
{
	for (auto id : INPUT_ID())										// nowのセット
	{
		state(id, static_cast<int>(_buf[_keyCon[static_cast<int>(id)]]));
	}
	
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)							// ｺﾝﾌｨｸﾞ切り替え
	{
		func = &KeyState::SetKeyConfing;
		TRACE("ｷｰｺﾝﾌｨｸﾞ起動\n");
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
			func = &KeyState::RefKeyData;							// 名前空間を書いてあげてどのclassのｱﾄﾞﾚｽかたどらせてあげる
			TRACE("ｷｰｺﾝﾌｨｸﾞ終了\n");
		}
	}

	if (_buf[KEY_INPUT_F1] && !modeKeyOld)							// ｺﾝﾌｨｸﾞ切り替え
	{
		func = &KeyState::RefKeyData;								// 名前空間を書いてあげてどのclassのｱﾄﾞﾚｽかたどらせてあげる
		TRACE("ｷｰｺﾝﾌｨｸﾞ終了\n");
	}
}
