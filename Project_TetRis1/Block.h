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

	static std::shared_ptr<InputState> _input;		// key�̊Ǘ�
	int _endCount;									// ��足�Ă������瑀��ł��Ȃ�����
	int _moveCount;									// �������߂̊�p
};

