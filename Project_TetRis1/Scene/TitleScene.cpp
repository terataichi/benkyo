#include "TitleScene.h"
#include "GameScene.h"
#include "Dxlib.h"
#include "../common/ImageMng.h"
#include "SceneMng.h"
#include "../Input/KeyState.h"

TitleScene::TitleScene()
{
	lpImageMng.GetID("€∫ﬁ", "image/titleLogo.png");
	lpImageMng.GetID("BG", "image/titleBG.png");
	lpImageMng.GetID("ZKEY", "image/start.png");
	_input = std::make_shared<KeyState>();
}

TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{

	(*_input).Update();												// ∑∞èÓïÒÇÃçXêV

	// º∞›êÿÇËë÷Ç¶
	if ((*_input).State(INPUT_ID::BTN_1).first && !(*_input).State(INPUT_ID::BTN_1).second)
	{
		return std::make_unique<GameScene>();
	}

	lpSceneMng.AddDrawQue({ IMAGE_ID("€∫ﬁ")[0],50,0,0,0,640,400,100,LAYER::UI });
	lpSceneMng.AddDrawQue({ IMAGE_ID("ZKEY")[0],150,250,0,0,640,400,100,LAYER::UI });
	lpSceneMng.AddDrawQue({ IMAGE_ID("BG")[0],0,0,0,0,640,400,200,LAYER::UI });


	return std::move(own);
}
