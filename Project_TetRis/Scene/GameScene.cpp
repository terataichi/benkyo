#include <algorithm>
#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <Scene\SceneMng.h>
#include <ImageMng.h>
#include <Block.h>


GameScene::GameScene()
{
	TRACE("¹Ş°Ñ¼°İ‚Ì¶¬\n");

	lpImageMng.GetID("GAME", "image/gameBG.png");		// ¹Ş°Ñ‰æ‘œ
	
	BlockState data;

	data = { BLOCK_TYPE::I ,
			{0,0},
			{0,415},
			{15,15} };

	_objList.emplace_back(new Block(data));
}

GameScene::~GameScene()
{
}

// XV
unique_Base GameScene::Update(unique_Base own)
{
	
	//lpSceneMng.AddDrawQue({ lpImageMng.GetID("G”wŒi")[0], 0,0 ,{0,0},{640,400} });						// ”wŒi•`‰æ

	for (auto data : _objList)
	{
		// XV
		(*data).Update();
	}

	for (auto data : _objList)
	{
		(*data).Draw();
	}
	
	/*[](){} ‚ç‚Ş‚¾‚µ‚«*/
	/* ‹ó‚É‚È‚Á‚½—v‘f‚ğÁ‚·	‚Ü‚Æ‚ß‚Ä‘‚¢‚½‚â‚Â*/

	return std::move(own);
}

