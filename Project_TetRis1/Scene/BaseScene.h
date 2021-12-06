#pragma once
#include <memory>
#include <vector>
#include "../Obj.h"
#include "../common/Vector2.h"
#include "../BLOCK_TYPE.h"

class BaseScene;	//	�������ߐ錾(���g�͂킩��Ȃ��̂Œ���)

enum class ACT_QUE
{
	NON,
	SHOT,
	CHECK_HIT,
	SHAKE,
	MAX
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;
using BlockInsT = std::pair<BLOCK_TYPE, bool>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;				// own ���g
	virtual void RunActQue(std::vector<ActQueT> actList);			// �S�Ă̼�݂ŕK�v����Ȃ����珃�����z�֐��ɂ͂��Ă��Ȃ�
	virtual void RunInsQue(BlockInsT& blockInsList);	// �ݽ�ݽ�œn���Ă�����

	Vector2 _screenPos;
};

