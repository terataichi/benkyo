#include <_DebugConOut.h>
#include "InputState.h"



InputState::InputState()
{
	for (auto id : INPUT_ID())
	{
		_state.try_emplace(INPUT_ID::LEFT, KeyPair{ 0,1 });
	}
}

InputState::~InputState()
{

}

const KeyMap& InputState::State(void) const
{
	return _state;
}

const KeyPair& InputState::State(INPUT_ID id) const
{

	static KeyPair defData = { 0,0 };

	try										// try…とりあえずやってね
	{
		return _state.at(id);				// IDの中身のoldとnowの情報を返す
	}
	catch(...)								// エラーが出たら捕まえる
	{
		AST();

		return defData;			// staticで最初から領域を取っておくことで安全に返す
								// private で謎の変数を作って置くもよし。両方完全に安全なわけではない

		/*return KeyPair{ 0,0 };*/ // これだと参照しようとしたときにﾛｰｶﾙ変数だから消えてしまっているのでよろしくない
	}

}

bool InputState::state(INPUT_ID id, int data)
{
	if (_state.find(id) != _state.end())
	{
		_state[id].first = data;
		return true;
	}

	return false;
}

void InputState::SetOld(void)
{

}
