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
	const KeyMap& State(void)const;					// •Ô‚·‚¾‚¯
	const KeyPair& State(INPUT_ID id)const;			// ID‚Ì’†g‚Ìold‚Ænow‚ğæ“¾
	bool state(INPUT_ID id ,int data);

private:
	KeyMap _state;
};

