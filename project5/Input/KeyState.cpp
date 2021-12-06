#include <DxLib.h>
#include "../_Debug/_DebugConOut.h"
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

	FILE *fp = NULL;														// ﾌｧｲﾙﾎﾟｲﾝﾀｰ

	fopen_s(&fp, "data/key.dat", "rb");										// 開きます
	if (fp != nullptr)
	{
		_keyCon.resize(static_cast<int>(end(INPUT_ID())));
		TRACE("読み込んだｷｰを設定します。\n");
		fread(_keyCon.data(), sizeof(_keyCon[0]) * _keyCon.size(), 1, fp);	// 読み込みます
		fclose(fp);															// 閉じます
	}
	else
	{	
		TRACE("ﾃﾞﾌｫﾙﾄｷｰを設定します。\n");
		// ﾌｧｲﾙに何もなかったらﾃﾞﾌｫﾙﾄｾｯﾃｲ
		_keyCon = _keyConDef;
	}

	modeKeyOld = 1;													// 

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
		_confID = begin(INPUT_ID());
		func = &KeyState::SetKeyConfing;
		TRACE("ｷｰｺﾝﾌｨｸﾞ起動\n");
	}
}

void KeyState::SetKeyConfing(void)
{

	if (_buf[KEY_INPUT_F1] && !modeKeyOld)						// ｺﾝﾌｨｸﾞ切り替え
	{
		func = &KeyState::RefKeyData;							// 名前空間を書いてあげてどのclassのｱﾄﾞﾚｽかたどらせてあげる
		TRACE("ｷｰｺﾝﾌｨｸﾞ終了\n");
		return;
	}

	// ﾗﾑﾀﾞ式で同じｷｰが設定されているか
	auto checkKey = [&](int id)
	{
		for (auto ckId = begin(INPUT_ID()); ckId < _confID; ++ckId)
		{
			if (_keyCon[static_cast<int>(ckId)] == id)			// ID ﾁｪｯｸ
			{
				return false;
			}
		}
		return true;
	};

	for (int id = 0; id < sizeof(_buf); id++)
	{
		if (!checkKey(id))										// 引数として
		{
			continue;											// もう一回forやってね
		}

		if (_buf[id] && !_buf[KEY_INPUT_F1])
		{
			_keyCon[static_cast<int>(_confID)] = id;
			++_confID;											// 前演算じゃないと何を++するかわかってくれない

			if (_confID >= end(_confID))						// 設定が全部完了したら終了する
			{
				// ﾌｧｲﾙへの書き込み
				FILE *fp = NULL;								// ﾌｧｲﾙﾎﾟｲﾝﾀｰ

				fopen_s(&fp, "data/key.dat", "wb");				// ﾌｧｲﾙopen

				if (fp != nullptr)
				{
					fwrite(_keyCon.data(), sizeof(_keyCon[0]) * _keyCon.size(), 1, fp);	// 書き込みます
					fclose(fp);															// 閉じます

					TRACE("ｷｰｺﾝﾌｨｸﾞ終了\n");
					func = &KeyState::RefKeyData;				// 名前空間を書いてあげてどのclassのｱﾄﾞﾚｽかたどらせてあげる
					break;
				}
				else
				{
					AST();
				}
			}

			TRACE("%d/%d番目のｷｰ設定\n",
				static_cast<int>(_confID),
				end(INPUT_ID())
			);
		}
	}
}
