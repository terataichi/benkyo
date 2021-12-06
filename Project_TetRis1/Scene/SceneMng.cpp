#include <Dxlib.h>
#include <iostream>
#include <algorithm>
#include "../_Debug/_DebugDispOut.h"
#include "../common/ImageMng.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "BaseScene.h"
#include "../Block.h"

SceneMng *SceneMng::sInstance = nullptr;


void SceneMng::Draw(void)
{
	_dbgAddDraw();											// ���ޯ��p�̕`��

	// �`��̏��Ԃ̕��ёւ�
	std::sort(_drawList.begin(), _drawList.end(),
		[](DrawQueT &left, DrawQueT &right) {

		// ���ްײ�ނ�1����ׂĂ����A�����ڲ԰�D�悾����ڲ԰���炻�낦�ē���ڲ԰�������ꍇ�����žޯĵ��ް���͂��߂ē���ւ���
		return std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(left), std::get<static_cast<int>(DRAW_QUE::ZODER)>(left)) 
				>
				std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(right), std::get<static_cast<int>(DRAW_QUE::ZODER)>(right));
	});

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// �`��ڲ԰��`��Ӱ�ނ̏����l��ݒ肷��
	LAYER drawLayer = begin(LAYER());
	int blendMode = DX_BLENDMODE_NOBLEND;
	int blendModeNum = 0;

	// Que�̕`����ݒ�
	SetDrawScreen(_layerGID);
	ClsDrawScreen();
	SetDrawBlendMode(blendMode, blendModeNum);

	// �����ɂ��܂��Ă���Que��`�悷��
	for (auto dQue : _drawList)
	{

		// tie�ɏ����΂炵�Ă��炤���߂̕ϐ������
		Vector2dbl pos;
		Vector2 upLeftPos, size;
		int id;
		LAYER layer;

		// �O�̷���̓��e���m��
		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		// tie �����܂Ƃ߂Ď��o���Ă΂�΂�ɂ��Ă����		 ignore �ǂݔ�΂��Ă����
		std::tie(id, pos.x, pos.y, upLeftPos.x, upLeftPos.y, size.x, size.y, std::ignore, layer) = dQue;	// �������� tie ���΂炵�Ă����
		
		if ((layer != drawLayer) || (blendModeOld != blendMode) || (blendModeNumOld != blendModeNum))
		{
			// _layerGID�ɏ��������e���o�b�N�o�b�t�@�ɕ`�悷��
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(layPos.x, layPos.y, 1.0, 0, _layerGID, true);

			// ����Que�̂��߂̏��������āA�`�����ꎞ�`���ɐݒ肷��
			SetDrawScreen(_layerGID);
			SetDrawBlendMode(blendMode, blendModeNum);
			ClsDrawScreen();
		}

		// ���S�`��Ȃ̂Ŕ����̓s��������
		DrawRectGraph(
			static_cast<int>(pos.x),
			static_cast<int>(pos.y),
			upLeftPos.x,
			upLeftPos.y,
			size.x,
			size.y,
			id,
			true
		);
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SetDrawBlendMode(blendMode, blendModeNum);
	DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _layerGID, true);

	ScreenFlip();	// ����ʂ���\��ʂ�
}

void SceneMng::Sound(void)
{
	for (auto sQue : _soundList)
	{
		PlaySoundMem(std::get<static_cast<int>(SOUND_QUE::SOUND)>(sQue), DX_PLAYTYPE_BACK, std::get<static_cast<int>(SOUND_QUE::LOOP)>(sQue));
	}
}

SceneMng::SceneMng() :ScreenSize{ 640,400 }, GameScreenSize{ 192 , 390 }, ScreenCenter{ ScreenSize / 2 }, GameScreenOffset{ BLOCK_SIZE * 15,16 }
{
	_gameCount = 0;
}

SceneMng::~SceneMng()
{

}

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<TitleScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		_dbgStartDraw();

		_drawList.clear();	// �v�f�����ׂď����Ă����
		_soundList.clear();

		_activeScene = (*_activeScene).Update(std::move(_activeScene));							// (*)�����邱�Ƃɂ���Ľϰ��߲���̊Ǘ����Ă��钆�g	->�Œ��ڌ��Ă��������ǂ��ł��m�ۂ�������������邪�ނ����Ȃ�

		Draw();

		(*_activeScene).RunActQue(std::move(_actList));											// ����move���ēn���Ă�����


		(*_activeScene).RunInsQue(_blockInsList);

		Sound();

		_gameCount++;																			// �ްѶ���
	}
}

bool SceneMng::AddSoundQue(SoundQueT sQue)
{
	_soundList.emplace_back(sQue);
	return true;
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

bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);
	return true;
}

bool SceneMng::AddBlockInsQue(BlockInsT bQue)
{
	_blockInsList = bQue;
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
	_layerGID = MakeScreen(ScreenSize.x, ScreenSize.y, true);

	_dbgSetup(255);									// ���ޯ�ޗp

	return false;
}
