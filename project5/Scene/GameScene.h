#pragma once
#include <vector>
#include "BaseScene.h"
#include "Obj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;
private:
	std::vector<Obj*>obj;
};

