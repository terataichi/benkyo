#include "TitleScene.h"
#include "GameScene.h"
#include "Dxlib.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	// ��ݐ؂�ւ�
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return std::make_unique<GameScene>();
	}

	return std::move(own);
}
