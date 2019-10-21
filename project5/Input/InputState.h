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
	virtual void Update(void) = 0;
	const KeyMap& State(void)const;					// 返すだけ
	const KeyPair& State(INPUT_ID id)const;			// IDの中身のoldとnowを取得
	bool state(INPUT_ID id ,int data);				// set
	void SetOld(void);


private:

	KeyMap _state;
};

