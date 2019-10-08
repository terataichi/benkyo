#pragma once
#include <memory>

class BaseScene;	//	�������ߐ錾(���g�͂킩��Ȃ��̂Œ���)

using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;	// own ���g
};

