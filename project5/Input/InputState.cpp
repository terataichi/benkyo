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
	// ID�̒��g��old��now�̏���Ԃ�
	return data;
}
