#pragma once
#include "BaseScene.h"
#include <Input/InputState.h>

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base own)override;
private:
	std::shared_ptr<InputState> _input;		// key‚ÌŠÇ—
};

