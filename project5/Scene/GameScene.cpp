#include <algorithm>
#include <DxLib.h>
#include <time.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <SoundMng.h>
#include <Player.h>
#include <Enemy.h>
#include <Bullet.h>
#include "SceneMng.h"
#include <Scene\func\FuncBullet.h>
#include <Scene\func\FuncCheckHit.h>


GameScene::GameScene()
{
	// ﾒﾝﾊﾞｰ関数の初期化
	InitFunc();

	// ｼｰﾄﾞ値の変更
	srand((unsigned int)time(NULL));

	TRACE("ｹﾞｰﾑｼｰﾝの生成\n");

	// ｲﾒｰｼﾞの初期化
	lpImageMng.GetID("ｷｬﾗ", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("弾", "image/shot.png", { 8,3 }, { 1,2 });
	lpImageMng.GetID("敵爆発", "image/en_blast.png", { 64,64 }, { 5,1 });
	lpImageMng.GetID("ｷｬﾗ爆発", "image/pl_blast.png", { 64,64 }, { 4,1 });

	// ﾌﾟﾚｲﾔｰの追加
	_objList.emplace_back(
		new Player({ lpSceneMng.GameScreenSize.x / 2.0,lpSceneMng.GameScreenSize.y - 16.0}, { 30,32 })
	);

	double ofSet = 0;			// ｵﾌｾｯﾄをいじる

	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{		

			MoveState tmpMoveState;			// 処理					最終地点
			tmpMoveState.emplace_back(MOVE_TYPE::WAIT, Vector2dbl{ (10.0 * ((y * 10) + x)),0.0 });
			tmpMoveState.emplace_back(MOVE_TYPE::SIGMOID, Vector2dbl{static_cast<double>((lpSceneMng.GameScreenSize.x / 4) + ((lpSceneMng.GameScreenSize.x / 2) * !((x % 2)))), (lpSceneMng.GameScreenSize.y * (5.0 / 6.0)) - (100 * ((((y * 10) + x) % 6) / 4)) });
			tmpMoveState.emplace_back(MOVE_TYPE::SPIRAL, Vector2dbl{ static_cast<double>((lpSceneMng.GameScreenSize.x / 4) + ((lpSceneMng.GameScreenSize.x / 2) * !((x % 2)))), (lpSceneMng.GameScreenSize.y * (5.0 / 6.0)) - 50 });
			tmpMoveState.emplace_back(MOVE_TYPE::PITIN, Vector2dbl{ (30.0 * 3.0) + (35.0 * x), 50 + (40.0 * y) });
			tmpMoveState.emplace_back(MOVE_TYPE::LR, Vector2dbl{ (30.0 * 3.0) + (35.0 * x), 50 + (40.0 * y) });
			tmpMoveState.emplace_back(MOVE_TYPE::SCALE, Vector2dbl{ static_cast<double>(lpSceneMng.GameScreenSize.x / 2), static_cast<double>(lpSceneMng.GameScreenSize.y / 3) });
			tmpMoveState.emplace_back(MOVE_TYPE::ATTACK, Vector2dbl{ 0.0,0.0 });
			tmpMoveState.emplace_back(MOVE_TYPE::PITIN, Vector2dbl{ (30.0 * 3.0) + (35.0 * x), 50 + (40.0 * y) });

			// ｵﾌｾｯﾄの計算
			switch ((x % 2))
			{
			case 0:
				ofSet = (-15);
				break;
			case 1:
				ofSet = 15;
				break;
			default:
				AST();
				ofSet = 0;
				break;
			}

			//type		pos		size																						15はｵﾌｾｯﾄ
			EnemyState data = { static_cast<ENEMY_TYPE>(((y * 10) + x) / 20 % 3),
								{static_cast<double>(lpSceneMng.GameScreenSize.x * (((y * 10) + x) % 2)) + ofSet,  static_cast<double>(330 / 2)*((((y * 10) + x) / 2) % 3) + 15},
								{30, 32},
								tmpMoveState };
			
			_objList.emplace_back(new Enemy(data));

		}
	}
	
	// ｻｳﾝﾄﾞの初期化
	lpSoundMng.GetID("弾", "sound/shot1.mp3");
}

GameScene::~GameScene()
{
}

// 更新
unique_Base GameScene::Update(unique_Base own)
{

	// 敵のｱﾀｯｸﾌﾗｸﾞ管理用関数
	auto CheckAt = [](sharedObj& obj)
	{
		// ｴﾈﾐｰが攻撃してほしい
		if ((*obj).unitID() == UNIT_ID::ENEMY)
		{
			// ﾗﾝﾀﾞﾑで攻撃してほしい
			if (rand() % 3000 == 0)
			{
				return true;
			}
		}
		return false;
	};

	// ﾌﾟﾚｲﾔｰのｵﾌﾞｼﾞｪの情報を取得
	auto plObj = std::find_if(_objList.begin(), _objList.end(), [&](sharedObj &obj) {
		return (*obj).unitID() == UNIT_ID::PLAYER;
	});

	for (auto data : _objList)
	{
		// 結果を返す
		if (CheckAt(data))
		{
			(*data).SetAttack(true);
		}
		else
		{
			(*data).SetAttack(false);

		}

		// 更新
		(*data).Update(*plObj);
	}

	// 描あ
	for (auto data : _objList)
	{
		(*data).Draw();
	}
	


	/*[](){} らむだしき*/
	//空になった要素を消す
	_objList.erase(std::remove_if(															// 中身を消すやつ 要素は残るからerase
								_objList.begin(),											// ﾁｪｯｸ範囲の開始
								_objList.end(),												// ﾁｪｯｸ範囲の終了地点
								[](sharedObj&obj) {return (*obj).isDead(); }				// ﾗﾑﾀﾞ式
								),
						_objList.end());

	return std::move(own);
}

void GameScene::RunActQue(std::vector<ActQueT> actList)
{
	for (auto actQue : actList)
	{
		try
		{
			funcQue.at(actQue.first)(actQue, _objList);
		}
		catch(...)
		{
			// なんかｴﾗｰが出たら
			AST();
		}
	}
}

void GameScene::InitFunc(void)
{
	// 処理の登録
	funcQue[ACT_QUE::SHOT] = FuncBullet();
	funcQue[ACT_QUE::CHECK_HIT] = FuncCheckHit();
}

