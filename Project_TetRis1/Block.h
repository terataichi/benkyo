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

	static std::shared_ptr<InputState> _input;		// keyの管理
	int _endCount;									// 一定ｶｳﾝﾄたったら操作できなくする
	int _moveCount;									// 動くための基準用
};

