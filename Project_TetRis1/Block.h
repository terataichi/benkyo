#pragma once
#include "Obj.h"
#include "BLOCK_TYPE.h"
#include "Input/InputState.h"
#include "Input/KeyState.h"
#include "Input/INPUT_ID.h"


class Block :
	public Obj
{
public:
	Block();
	Block(BLOCK_TYPE type);
	~Block();

	void Update() override;

private:
	void Init(BLOCK_TYPE type);
	void BlockInit(BLOCK_TYPE type);

	static std::shared_ptr<InputState> _input;		// key‚ÌŠÇ—
	int _endCount;									// ˆê’è¶³İÄ‚½‚Á‚½‚ç‘€ì‚Å‚«‚È‚­‚·‚é
	int _moveCount;									// “®‚­‚½‚ß‚ÌŠî€—p
};

