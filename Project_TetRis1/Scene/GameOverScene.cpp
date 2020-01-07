#include "GameOverScene.h"
#include "TitleScene.h"
#include "Dxlib.h"
#include <ImageMng.h>
#include <SceneMng.h>
#include <MapChip.h>


GameOverScene::GameOverScene()
{
}


GameOverScene::~GameOverScene()
{
}

unique_Base GameOverScene::Update(unique_Base own)
{
	// º∞›êÿÇËë÷Ç¶
	if (CheckHitKey(KEY_INPUT_Z))
	{
		return std::make_unique<TitleScene>();
	}

	lpMapChip.GemeOverDraw();
	lpSceneMng.AddDrawQue({ IMAGE_ID("îwåi")[0],0,0,0,0,640,400,-1,LAYER::UI });		// ògÇÃï`âÊ


	return std::move(own);
}