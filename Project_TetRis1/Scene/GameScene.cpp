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
	// ���ޒl�̕ύX
	srand((unsigned int)time(NULL));

	TRACE("�ްѼ�݂̐���\n");

	lpImageMng.GetID("�w�i", "image/gameBG.png");
	lpImageMng.GetID("ϯ��", "image/gameBG.png");
	// ��ۯ�
	lpImageMng.GetID("I", "image/gameBG.png");
	lpImageMng.GetID("O", "image/gameBG.png");
	lpImageMng.GetID("T", "image/gameBG.png");
	lpImageMng.GetID("J", "image/gameBG.png");
	lpImageMng.GetID("L", "image/gameBG.png");
	lpImageMng.GetID("S", "image/gameBG.png");
	lpImageMng.GetID("Z", "image/gameBG.png");

	// ϯ�ߏ�����
	lpMapChip.InitMap();

	_objList.emplace_back(new Block(rand(BLOCK_TYPE())));
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
			if (lpMapChip.CheckGameOver())
			{
				return std::make_unique<GameOverScene>();
			}
		}


	if (lpMapChip.CheckLine())
	{
		lpMapChip.DeleteLine();
	}
	// �`��
	for (auto data : _objList)
	{
		(*data).Draw();
	}
	lpMapChip.GameDraw();		// ϯ�����߂̕`��

	/*[](){} ��ނ�����*/
	//��ɂȂ����v�f������
	_objList.erase(std::remove_if(															// ���g��������� �v�f�͎c�邩��erase
								_objList.begin(),											// �����͈͂̊J�n
								_objList.end(),												// �����͈͂̏I���n�_
								[](sharedObj&obj) {return (*obj).isDead(); }				// ���ގ�
								),
						_objList.end());

	lpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0],0,0,0,0,640,400,-1,LAYER::UI });		// �g�̕`��

	return std::move(own);
}

void GameScene::RunInsQue(BlockInsT& blockInsList)
{
	// �׸ނ�true��������
	if (blockInsList.second)
	{
		_objList.emplace_back(new Block(blockInsList.first));
		blockInsList.second = false;
	}
}
