#include "TitleScene.h"
#include "GameScene.h"
#include "Dxlib.h"
#include <ImageMng.h>
#include <SceneMng.h>

TitleScene::TitleScene()
{
	lpImageMng.GetID("€∫ﬁ", "image/titleLogo.png");
	lpImageMng.GetID("BG", "image/titleBG.png");
	lpImageMng.GetID("ZKEY", "image/start.png");

}

TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	// º∞›êÿÇËë÷Ç¶
	if (CheckHitKey(KEY_INPUT_Z))
	{
		return std::make_unique<GameScene>();
	}

	lpSceneMng.AddDrawQue({ IMAGE_ID("€∫ﬁ")[0],50,0,0,0,640,400,100,LAYER::UI });
	lpSceneMng.AddDrawQue({ IMAGE_ID("ZKEY")[0],150,250,0,0,640,400,100,LAYER::UI });
	lpSceneMng.AddDrawQue({ IMAGE_ID("BG")[0],0,0,0,0,640,400,200,LAYER::UI });


	return std::move(own);
}
