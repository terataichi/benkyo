#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;	//	�������ߐ錾(���g�͂킩��Ȃ��̂Œ���)

enum class ACT_QUE
{
	NON,
	SHOT
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;	// own ���g
	virtual void RunActQue(std::vector<ActQueT> actList);	// �S�Ă̼�݂ŕK�v����Ȃ����珃�����z�֐��ɂ͂��Ă��Ȃ�
};

