#include <algorithm>
#include <DxLib.h>
#include <time.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include "GameOverScene.h"
#include <ImageMng.h>
#include <SoundMng.h>
#include "SceneMng.h"
#include <Block.h>
#include <MapChip.h>

GameScene::GameScene()
{
	// ｼｰﾄﾞ値の変更
	srand((unsigned int)time(NULL));

	TRACE("ｹﾞｰﾑｼｰﾝの生成\n");

	lpImageMng.GetID("背景", "image/gameBG.png");
	lpImageMng.GetID("ﾏｯﾌﾟ", "image/gameBG.png");
	// ﾌﾞﾛｯｸ
	lpImageMng.GetID("I", "image/gameBG.png");
	lpImageMng.GetID("O", "image/gameBG.png");
	lpImageMng.GetID("T", "image/gameBG.png");
	lpImageMng.GetID("J", "image/gameBG.png");
	lpImageMng.GetID("L", "image/gameBG.png");
	lpImageMng.GetID("S", "image/gameBG.png");
	lpImageMng.GetID("Z", "image/gameBG.png");

	// ﾏｯﾌﾟ初期化
	lpMapChip.InitMap();

	_objList.emplace_back(new Block(rand(BLOCK_TYPE())));
}

GameScene::~GameScene()
{
}

// 更新
unique_Base GameScene::Update(unique_Base own)
{
	for (auto data : _objList)
		{
			// 更新
			(*data).Update();
			if (lpMapChip.CheckGameOver())
			{
				return std::make_unique<GameOverScene>();
			}
		}


	if (lpMapChip.CheckLine())
	{
		lpMapChip.DeleteLine();
	}
	// 描画
	for (auto data : _objList)
	{
		(*data).Draw();
	}
	lpMapChip.GameDraw();		// ﾏｯﾌﾟﾁｯﾌﾟの描画

	/*[](){} らむだしき*/
	//空になった要素を消す
	_objList.erase(std::remove_if(															// 中身を消すやつ 要素は残るからerase
								_objList.begin(),											// ﾁｪｯｸ範囲の開始
								_objList.end(),												// ﾁｪｯｸ範囲の終了地点
								[](sharedObj&obj) {return (*obj).isDead(); }				// ﾗﾑﾀﾞ式
								),
						_objList.end());

	lpSceneMng.AddDrawQue({ IMAGE_ID("背景")[0],0,0,0,0,640,400,-1,LAYER::UI });		// 枠の描画

	return std::move(own);
}

void GameScene::RunInsQue(BlockInsT& blockInsList)
{
	// ﾌﾗｸﾞがtrueだったら
	if (blockInsList.second)
	{
		_objList.emplace_back(new Block(blockInsList.first));
		blockInsList.second = false;
	}
}
