#pragma once
#include "BaseScene.h"

class GameOverScene :
	public BaseScene
{
public:
	GameOverScene();
	~GameOverScene();
	unique_Base Update(unique_Base own)override;
};

