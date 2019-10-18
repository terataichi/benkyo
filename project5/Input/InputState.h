#pragma once
#include <map>
#include "INPUT_ID.h"
using KeyPair = std::pair<int, int>;
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	const KeyMap& State(void)const;					// •Ô‚·‚¾‚¯
	const KeyPair& State(INPUT_ID id)const;			// ID‚Ì’†g‚Ìold‚Ænow‚ğæ“¾
	bool state(INPUT_ID id ,int data);				// set
	void SetOld(void);

private:

	KeyMap _state;
};

