#include "TitleScene.h"
#include <_DebugConOut.h>
#include "GameScene.h"
#include "Dxlib.h"
#include "ImageMng.h"
#include <Scene\SceneMng.h>



TitleScene::TitleScene()
{
	TRACE("À²ÄÙ¼°İ‚Ì¶¬\n");

	lpImageMng.GetID("À²ÄÙ", "image/titleLogo.png");
	lpImageMng.GetID("T”wŒi", "image/titleBG.png");
	lpImageMng.GetID("‰Ÿ‚µ‚Ä‚Ë", "image/start.png");	

}

TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	
	Draw();											// •`‰æ

	if (CheckHitKey(KEY_INPUT_Z))
	{
		return std::make_unique<GameScene>();
	}

	return std::move(own);
}

void TitleScene::Draw(void)
{
	lpSceneMng.AddDrawQue({ lpImageMng.GetID("T”wŒi")[0] ,0,0 ,{0,0},{640,400} });
	lpSceneMng.AddDrawQue({ lpImageMng.GetID("À²ÄÙ")[0],50,30,{0,0},{540,174} });
	lpSceneMng.AddDrawQue({ lpImageMng.GetID("‰Ÿ‚µ‚Ä‚Ë")[0],140,300,{0,0},{320,62} });
}
