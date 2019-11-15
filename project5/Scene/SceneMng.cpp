#include <Dxlib.h>
#include <iostream>
#include <algorithm>
#include <_Debug\_DebugDispOut.h>
#include <ImageMng.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"

SceneMng *SceneMng::sInstance = nullptr;

LAYER begin(LAYER)
{
	return LAYER::BG;
}
LAYER end(LAYER)
{
	return LAYER::MAX;
}
LAYER operator*(LAYER key)
{
	return key;
}
LAYER operator++(LAYER & key)
{
	// �K��̌^��Ԃ��Ă����
	// std::underlying_type<>::type()

	return key = static_cast<LAYER>(std::underlying_type<LAYER>::type(key) + 1);
}

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

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	
	// �����ɂ��܂��Ă���Que��`�悷��
	for (auto dQue : _drawList)
	{

		// tie�ɏ����΂炵�Ă��炤���߂̕ϐ������
		double x, y, rad;
		int id;
		LAYER layer;
		// tie �����܂Ƃ߂Ď��o���Ă΂�΂�ɂ��Ă����		 ignore �ǂݔ�΂��Ă����
		std::tie(id, x, y, rad, std::ignore, layer) = dQue;	// �������� tie ���΂炵�Ă����
		
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

	for (auto id : LAYER())
	{
		DrawGraph(0, 0, _screenID[id], true);
	}

	ScreenFlip();
}

SceneMng::SceneMng():ScreenSize{800,600}
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

	for (auto id : LAYER())
	{
		if (_screenID.find(id) == _screenID.end())
		{
			_screenID[id] = MakeScreen(ScreenSize.x, ScreenSize.y, true);
		}
	}

	_dbgSetup(200);									// ���ޯ�ޗp

	lpImageMng.GetID("�g", "image/frame.png");		// �g


	return false;
}
