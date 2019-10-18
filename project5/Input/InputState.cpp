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

	try										// try�c�Ƃ肠��������Ă�
	{
		return _state.at(id);				// ID�̒��g��old��now�̏���Ԃ�
	}
	catch(...)								// �G���[���o����߂܂���
	{
		AST();

		return defData;			// static�ōŏ�����̈������Ă������Ƃň��S�ɕԂ�
								// private �œ�̕ϐ�������Ēu�����悵�B�������S�Ɉ��S�Ȃ킯�ł͂Ȃ�

		/*return KeyPair{ 0,0 };*/ // ���ꂾ�ƎQ�Ƃ��悤�Ƃ����Ƃ���۰�ٕϐ�����������Ă��܂��Ă���̂ł�낵���Ȃ�
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
