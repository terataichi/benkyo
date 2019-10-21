#pragma once
#include <vector>
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void) override;
private:
	void RefKeyData(void);					// 
	void SetKeyConfing(void);				// �ݒ�p
	void (KeyState::*func)(void);			// �֐��߲���  �ϐ�		�����������Ȃ��ƕʂ̔F���������

	char _buf[256];							// ���̏��擾�p
	std::vector<int> _keyCon;				// ���̷���
	std::vector<int> _keyConDef;			// ��̫��

};

