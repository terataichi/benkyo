#include <Dxlib.h>
#include <iostream>
#include <algorithm>
#include <_Debug\_DebugDispOut.h>
#include <ImageMng.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"

SceneMng *SceneMng::sInstance = nullptr;


void SceneMng::Draw(void)
{
	_dbgAddDraw();											// ���ޯ��p�̕`��

	// �`��̏��Ԃ̕��ёւ�
	std::sort(_drawList.begin(), _drawList.end(),
		[](DrawQueT &left, DrawQueT &right) {

		// ���ްײ�ނ�1����ׂĂ����A�����ڲ԰�D�悾����ڲ԰���炻�낦�ē���ڲ԰�������ꍇ�����žޯĵ��ް���͂��߂ē���ւ���
		return std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(left), std::get<static_cast<int>(DRAW_QUE::ZODER)>(left)) 
				<
				std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(right), std::get<static_cast<int>(DRAW_QUE::ZODER)>(right));
	});

	for (auto layer : LAYER())
	{
		SetDrawScreen(_screenID[layer]);
		ClsDrawScreen();

	}
	// �����ɂ��܂��Ă���Que��`�悷��
	for (auto dQue : _drawList)
	{

		// tie�ɏ����΂炵�Ă��炤���߂̕ϐ������
		double x, y, rad;
		int id;
		LAYER layer;
		// tie �����܂Ƃ߂Ď��o���Ă΂�΂�ɂ��Ă����		 ignore �ǂݔ�΂��Ă����
		std::tie(id, x, y, rad, std::ignore, layer) = dQue;	// �������� tie ���΂炵�Ă����
		
		// ���̽�ذ݂�ID��������炻��ڲ԰�ɏ������߂�
		if (GetDrawScreen() != _screenID[layer])
		{
			SetDrawScreen(_screenID[layer]);
			ClsDrawScreen();
		}

		// ���S�`��Ȃ̂Ŕ����̓s��������
		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true
		);
	}

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// �eڲ԰�̽�ذ݂�`�悷��
	for (auto layer : LAYER())
	{
		DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _screenID[layer], true);
	}

	ScreenFlip();	// ����ʂ���\��ʂ�
}

SceneMng::SceneMng() :ScreenSize{ 800,600 }, GameScreenSize{ 500 , 390 }, ScreenCenter{ ScreenSize / 2 }, GameScreenOffset{ (ScreenSize - GameScreenSize) / 2 }
{
	
}

SceneMng::~SceneMng()
{

}

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();

		_drawList.clear();	// �v�f�����ׂď����Ă����
		
		AddDrawQue({ IMAGE_ID("�g")[0],400,300,0,0,LAYER::UI });		// �g�̕`��

		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// (*)�����邱�Ƃɂ���Ľϰ��߲���̊Ǘ����Ă��钆�g	->�Œ��ڌ��Ă��������ǂ��ł��m�ۂ�������������邪�ނ����Ȃ�
		Draw();

	}
	// delete _activeScene;
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		// �摜ID���s���������̂Œǉ����܂���
		return false;
	}

	// Que��ǉ�
	//_drawList.push_back�͌Â���
	_drawList.emplace_back(dQue);

	return true;
}

bool SceneMng::SysInit(void)
{
	SetWindowText("1916025_terasaki");

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);	//��ذݻ���

	ChangeWindowMode(true);							//ture:window false:�ٽ�ذ�

	if (DxLib_Init() == -1)
	{
		return false;								//DXײ���؏���������
	}
	SetDrawScreen(DX_SCREEN_BACK);					//�ЂƂ܂��ޯ��ޯ̧�ɕ`��

	// �eڲ԰�p�̽�ذ݂��
	for (auto id : LAYER())
	{
		_screenID.try_emplace(id, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	}

	_dbgSetup(255);									// ���ޯ�ޗp

	lpImageMng.GetID("�g", "image/frame.png");		// �g


	return false;
}
