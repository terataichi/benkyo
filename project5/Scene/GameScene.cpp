#include <algorithm>
#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>
#include <Bullet.h>
#include "SceneMng.h"


GameScene::GameScene()
{
	TRACE("�ްѼ�݂̐���\n");

	lpImageMng.GetID("���", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("�e", "image/shot.png", { 8,3 }, { 1,2 });
	lpImageMng.GetID("�G����", "image/en_blast.png", { 64,64 }, { 5,1 });
	lpImageMng.GetID("��ה���", "image/pl_blast.png", { 64,64 }, { 4,1 });

	_objList.emplace_back(
		new Player({ lpSceneMng.GameScreenSize.x / 2.0,lpSceneMng.GameScreenSize.y - 16.0}, { 0,0 })
	);

	double ofSet = 0;			// �̾�Ă�������

	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{		

			MoveState tmpMoveState;			// ����					�ŏI�n�_
			tmpMoveState.emplace_back(MOVE_TYPE::WAIT, Vector2dbl{ (30.0 * ((y * 10) + x)),0.0 });
			tmpMoveState.emplace_back(MOVE_TYPE::SIGMOID, Vector2dbl{static_cast<double>((lpSceneMng.GameScreenSize.x / 4) + ((lpSceneMng.GameScreenSize.x / 2) * !((x % 2)))), (lpSceneMng.GameScreenSize.y * (5.0 / 6.0)) - (100 * ((((y * 10) + x) % 6) / 4)) });
			tmpMoveState.emplace_back(MOVE_TYPE::SPIRAL, Vector2dbl{ static_cast<double>((lpSceneMng.GameScreenSize.x / 4) + ((lpSceneMng.GameScreenSize.x / 2) * !((x % 2)))), (lpSceneMng.GameScreenSize.y * (5.0 / 6.0)) - 50 });
			tmpMoveState.emplace_back(MOVE_TYPE::PITIN, Vector2dbl{ (30.0 * 3.0) + (35.0 * x), 50 + (40.0 * y) });
			tmpMoveState.emplace_back(MOVE_TYPE::LR, Vector2dbl{ (30.0 * 3.0) + (35.0 * x), 50 + (40.0 * y) });
			tmpMoveState.emplace_back(MOVE_TYPE::SCALE, Vector2dbl{ static_cast<double>(lpSceneMng.GameScreenSize.x / 2), static_cast<double>(lpSceneMng.GameScreenSize.y / 3) });

			// �̾�Ă̌v�Z
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

			//type		pos		size																						15�͵̾��
			EnemyState data = { ENEMY_TYPE::A,
								{static_cast<double>(lpSceneMng.GameScreenSize.x * (((y * 10) + x) % 2)) + ofSet,  static_cast<double>(330 / 2)*((((y * 10) + x) / 2) % 3) + 15},
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

// �X�V
unique_Base GameScene::Update(unique_Base own)
{
	
	for (auto data : _objList)
	{
		// �X�V
		(*data).Update();
	}

	for (auto data : _objList)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			// ���S�׸�
			(*data).SetAlive(false);
		}
		(*data).Draw();
	}
	
	/*[](){} ��ނ�����*/
	/* ��ɂȂ����v�f������	�܂Ƃ߂ď��������*/
	_objList.erase(std::remove_if(															// ���g��������� �v�f�͎c�邩��erase
								_objList.begin(),											// �����͈͂̊J�n
								_objList.end(),												// �����͈͂̏I���n�_
								[](sharedObj&obj) {return (*obj).isDead(); }				// ���ގ�
								),
						_objList.end());

	return std::move(own);
}

void GameScene::RunActQue(std::vector<ActQueT> actList)
{
	for (auto actQue : actList)
	{
		switch (actQue.first)
		{
		case ACT_QUE::SHOT:
			_objList.emplace_back(new Bullet(actQue.second.pos()));
			break;
		}
	}

}

