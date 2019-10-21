#include <DxLib.h>
#include "KeyState.h"



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

	func = &KeyState::RefKeyData;									// 名前空間を書いてあげてどのclassのｱﾄﾞﾚｽかたどらせてあげる

}


KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	SetOld();								// new を old　に書く
	GetHitKeyStateAll(_buf);				// 全てのｷｰ情報を取得
	(this->*func)();						// this 自分自身
}

void KeyState::RefKeyData(void)
{

}

void KeyState::SetKeyConfing(void)
{

}
