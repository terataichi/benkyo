#include "InputState.h"



InputState::InputState()
{

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
	KeyPair data;
	// IDの中身のoldとnowの情報を返す
	return data;
}
