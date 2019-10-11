#include <algorithm>
#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>


GameScene::GameScene()
{
	TRACE("ｹﾞｰﾑｼｰﾝの生成\n");
	TRACE("今のｼｰﾝは");
	lpImageMng.GetID("ｷｬﾗ", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("弾", "image/shot.png", { 8,3 }, { 1,2 });
	lpImageMng.GetID("敵爆発", "image/en_blast.png", { 64,64 }, { 5,1 });
	lpImageMng.GetID("ｷｬﾗ爆発", "image/pl_blast.png", { 64,64 }, { 4,1 });

	_objList.emplace_back(
		new Player({ 100,100 }, { 0,0 })
	);
	_objList.emplace_back(
		new Player({ 200,100 }, { 0,0 })
	);

	/*obj[0] = new Obj("image/char.png", { 0, 0 }, 10, 10, 30, 32);
	obj[1] = new Obj("image/char.png", { 100, 100 }, 10, 10, 30, 32);*/

}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	
	for (auto data : _objList)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			(*data).SetAlive(false);
		}
		(*data).Draw();
	}
	
	//std::remove_if(
	//	_objList.begin(),	// ﾁｪｯｸ範囲の開始
	//	_objList.end(),		// ﾁｪｯｸ範囲の終了地点
	//	[](sharedObj&obj) {return (*obj).isDead(); }
	//	);

	return std::move(own);
}

