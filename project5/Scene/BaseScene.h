#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;	//	ÌßÛÄÀ²ÌßéŒ¾(’†g‚Í‚í‚©‚ç‚È‚¢‚Ì‚Å’ˆÓ)

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
	virtual unique_Base Update(unique_Base own) = 0;	// own ©g
	virtual void RunActQue(std::vector<ActQueT> actList);
};

