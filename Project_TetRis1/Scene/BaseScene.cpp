#include <DxLib.h>
#include "BaseScene.h"
#include "../common/ImageMng.h"
#include "../Scene/SceneMng.h"


BaseScene::BaseScene()
{
}

BaseScene::~BaseScene()
{
}

void BaseScene::RunActQue(std::vector<ActQueT> actList)
{
	actList.clear();
}

void BaseScene::RunInsQue(BlockInsT& blockInsList)
{
}
