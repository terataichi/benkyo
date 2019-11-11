#include <Dxlib.h>
#include <iostream>
#include <_Debug\_DebugDispOut.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"

SceneMng *SceneMng::sInstance = nullptr;

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// �����ɂ��܂��Ă���Que��`�悷��
	for (auto dataQue : _drawList)
	{
		// ���S�`��Ȃ̂Ŕ����̓s��������
		DrawRotaGraph(
			std::get<static_cast<int>(DRAW_QUE::X)>(dataQue),
			std::get<static_cast<int>(DRAW_QUE::Y)>(dataQue),
			1.0,
			std::get<static_cast<int>(DRAW_QUE::RAD)>(dataQue),
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dataQue),
			true
		);
	}
	// ��ڰ���ł��ꍇ
	// std::vector<_dra>
	//for (auto dataQue = _drawList.begin(); dataQue != _drawList.end(); dataQue++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(*dataQue),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(*dataQue),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(*dataQue),
	//		true);
	//}
	
	// ���@�@���@��
	// for (int no = 0; no < _drawList.size(); no++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(_drawList[no]),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(_drawList[no]),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_drawList[no]),
	//		true
	//	);
	//}


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
		_drawList.clear();	// �v�f�����ׂď����Ă����
		
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
	
	return false;
}
