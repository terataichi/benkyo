#include <algorithm>
#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <Scene\SceneMng.h>
#include <ImageMng.h>
#include <Block.h>


GameScene::GameScene()
{
	TRACE("�ްѼ�݂̐���\n");

	lpImageMng.GetID("GAME", "image/gameBG.png");		// �ްщ摜
	
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

// �X�V
unique_Base GameScene::Update(unique_Base own)
{
	
	//lpSceneMng.AddDrawQue({ lpImageMng.GetID("G�w�i")[0], 0,0 ,{0,0},{640,400} });						// �w�i�`��

	for (auto data : _objList)
	{
		// �X�V
		(*data).Update();
	}

	for (auto data : _objList)
	{
		(*data).Draw();
	}
	
	/*[](){} ��ނ�����*/
	/* ��ɂȂ����v�f������	�܂Ƃ߂ď��������*/

	return std::move(own);
}

