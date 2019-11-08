#pragma once
#include "BaseScene.h"
#include <Obj.h>

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base own)override;
private:
	void Draw(void);							// À²ÄÙ•`‰æ—p
};

