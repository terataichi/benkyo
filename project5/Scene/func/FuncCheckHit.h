#pragma once
#include "../BaseScene.h"
#include <vector>
#include "../../common/Vector2.h"

// �����蔻��
struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
private:
	int _posLength;			// ��޼ު�Ă̍��W�̋���
	int _sizeLength;		// ��޼ު�Ă̻��ނ̋���
};

