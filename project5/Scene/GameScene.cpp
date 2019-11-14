#include <algorithm>
#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>
#include "SceneMng.h"


GameScene::GameScene()
{
	TRACE("�ްѼ�݂̐���\n");

	lpImageMng.GetID("���", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("�e", "image/shot.png", { 8,3 }, { 1,2 });
	lpImageMng.GetID("�G����", "image/en_blast.png", { 64,64 }, { 5,1 });
	lpImageMng.GetID("��ה���", "image/pl_blast.png", { 64,64 }, { 4,1 });

	_objList.emplace_back(
		new Player({ 100,100 }, { 0,0 })
	);

	double ofSet = 0;			// �̾�Ă�������

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 10; x++)
		{		

			MoveState tmpMoveState;			// ����					�ŏI�n�_
			tmpMoveState.emplace_back(MOVE_TYPE::WAIT, Vector2dbl{ (30.0 * ((y * 10) + x)),0.0 });
			tmpMoveState.emplace_back(MOVE_TYPE::SIGMOID, Vector2dbl{ 200.0 + ((lpSceneMng.ScreenSize.x / 2) * !((x % 2))) ,(lpSceneMng.ScreenSize.y * (5.0 / 7.0)) - (200 * ((((y * 10) + x) % 6) / 4)) });
			tmpMoveState.emplace_back(MOVE_TYPE::SPIRAL, Vector2dbl{ 200.0 + ((lpSceneMng.ScreenSize.x / 2) * !((x % 2))),(lpSceneMng.ScreenSize.y * (5.0 / 7.0)) - 100 });
			//tmpMoveState.emplace_back(MOVE_TYPE::PITIN, Vector2dbl{ (35.0 * 7.0) + (35.0 * x),50 + (40.0 * y) });
			tmpMoveState.emplace_back( MOVE_TYPE::LR, Vector2dbl{ 180.0,0.0 });

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
								{static_cast<double>(800 * (((y * 10) + x) % 2)) + ofSet,  static_cast<double>(540 / 2)*((((y * 10) + x) / 2) % 3) + 15},
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

