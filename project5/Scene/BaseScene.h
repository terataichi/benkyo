#pragma once
#include <memory>
#include <vector>
#include "../Obj.h"
#include "../common/Vector2.h"

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

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;		// own ���g
	virtual void RunActQue(std::vector<ActQueT> actList);	// �S�Ă̼�݂ŕK�v����Ȃ����珃�����z�֐��ɂ͂��Ă��Ȃ�
	Vector2 _screenPos;
protected:
	void FadeInit(std::string fadeType);
	bool FadeUpdate(void);
private:
	int _fadeScrID;
	int _fadeCount;
	std::string _fadeType;
};

