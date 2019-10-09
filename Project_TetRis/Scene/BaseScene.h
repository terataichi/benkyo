#pragma once
#include <memory>

class BaseScene;	//	ÌßÛÄÀ²ÌßéŒ¾(’†g‚Í‚í‚©‚ç‚È‚¢‚Ì‚Å’ˆÓ)

using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;	// own ©g
};

