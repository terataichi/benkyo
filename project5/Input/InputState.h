#pragma once
#include <map>

enum class INPUT_ID
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	BTN_1,
	BTN_2,
	BTN_3,
	BTN_4,
	MAX
};

using KeyPair = std::pair<int, int>;
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	const KeyMap& State(void)const;					// 返すだけ
	const KeyPair& State(INPUT_ID id)const;			// IDの中身のoldとnowを取得
	bool state(INPUT_ID id ,int data);

private:
	KeyMap _state;
};

