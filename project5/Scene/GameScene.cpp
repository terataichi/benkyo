#include <algorithm>
#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>


GameScene::GameScene()
{
	TRACE("�ްѼ�݂̐���\n");
	TRACE("���̼�݂�");
	lpImageMng.GetID("���", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("�e", "image/shot.png", { 8,3 }, { 1,2 });
	lpImageMng.GetID("�G����", "image/en_blast.png", { 64,64 }, { 5,1 });
	lpImageMng.GetID("��ה���", "image/pl_blast.png", { 64,64 }, { 4,1 });

	_objList.emplace_back(
		new Player({ 100,100 }, { 0,0 })
	);

	_objList.emplace_back(
		new Player({ 200,100 }, { 0,0 })
	);

	EnemyState data; 

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{			//type			pos								size
			data = { ENEMY_TYPE::A, {200 + (x * 30), 100 + (y * 32)}, {0, 0} };

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

