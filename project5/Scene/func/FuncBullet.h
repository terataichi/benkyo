#pragma once
#include <Scene\BaseScene.h>
#include <vector>

// �֐��I�u�W�F�N�g����
struct FuncBullet
{
	bool operator()(ActQueT& actQue, std::vector<sharedObj>& objList);		// �������󂯎���Ēe���o������
private:
	static std::map<UNIT_ID, int> _MaxCount;								// �e�̍ő吔�̐ݒ�
};

