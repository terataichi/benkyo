#pragma once
#include <Scene\BaseScene.h>
#include <vector>
#include <Vector2.h>

// �����蔻��
struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
private:
	int _posLength;			// ��޼ު�Ă̍��W�̋���
	int _sizeLength;		// ��޼ު�Ă̻��ނ̋���
};

