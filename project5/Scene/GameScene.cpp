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

	lpImageMng.GetID("ｷｬﾗ", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("弾", "image/shot.png", { 8,3 }, { 1,2 });
	lpImageMng.GetID("敵爆発", "image/en_blast.png", { 64,64 }, { 5,1 });
	lpImageMng.GetID("ｷｬﾗ爆発", "image/pl_blast.png", { 64,64 }, { 4,1 });

	_objList.emplace_back(
		new Player({ 100,100 }, { 0,0 })
	);

	//_objList.emplace_back(
	//	new Player({ 200,100 }, { 0,0 })
	//);

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 10; x++)
		{		
			MoveState tmpMoveState;
			tmpMoveState.emplace_back(MOVE_TYPE::WAIT ,Vector2dbl{ 0.0,0.0 });
			tmpMoveState.emplace_back(MOVE_TYPE::PITIN, Vector2dbl{ 180.0,0.0 });
			tmpMoveState.emplace_back( MOVE_TYPE::LR, Vector2dbl{ 180.0,0.0 });

			//type		pos		size
			EnemyState data = { static_cast<ENEMY_TYPE>((int)x % 3),
								{static_cast<double>(800 * (x % 2)),  static_cast<double>((540/2)*((y / 2) % 3))},
								{0, 0},
								tmpMoveState };

			_objList.emplace_back(new Enemy(data));
		}
	}
	

	/*obj[0] = new Obj("image/char.png", { 0, 0 }, 10, 10, 30, 32);
	obj[1] = new Obj("image/char.png", { 100, 100 }, 10, 10, 30, 32);*/

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
	}

	for (auto data : _objList)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			// 死亡ﾌﾗｸﾞ
			(*data).SetAlive(false);
		}
		(*data).Draw();
	}
	
	/*[](){} らむだしき*/
	/* 空になった要素を消す	まとめて書いたやつ*/
	_objList.erase(std::remove_if(															// 中身を消すやつ 要素は残るからerase
								_objList.begin(),											// ﾁｪｯｸ範囲の開始
								_objList.end(),												// ﾁｪｯｸ範囲の終了地点
								[](sharedObj&obj) {return (*obj).isDead(); }				// ﾗﾑﾀﾞ式
								),
						_objList.end());

	return std::move(own);
}

