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
	// IDの中身のoldとnowの情報を返す
}
