#include "TitleScene.h"
#include <_DebugConOut.h>
#include "GameScene.h"
#include "Dxlib.h"
#include "ImageMng.h"
#include <Scene\SceneMng.h>



TitleScene::TitleScene()
{
	TRACE("���ټ�݂̐���\n");

	lpImageMng.GetID("����", "image/titleLogo.png");
	lpImageMng.GetID("T�w�i", "image/titleBG.png");
	lpImageMng.GetID("�����Ă�", "image/start.png");	

}

TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	
	Draw();											// �`��

	if (CheckHitKey(KEY_INPUT_Z))
	{
		return std::make_unique<GameScene>();
	}

	return std::move(own);
}

void TitleScene::Draw(void)
{
	lpSceneMng.AddDrawQue({ lpImageMng.GetID("T�w�i")[0] ,0,0 ,{0,0},{640,400} });
	lpSceneMng.AddDrawQue({ lpImageMng.GetID("����")[0],50,30,{0,0},{540,174} });
	lpSceneMng.AddDrawQue({ lpImageMng.GetID("�����Ă�")[0],140,300,{0,0},{320,62} });
}
