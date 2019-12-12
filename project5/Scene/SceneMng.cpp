#include <Dxlib.h>
#include <iostream>
#include <algorithm>
#include <_Debug\_DebugDispOut.h>
#include <ImageMng.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "BaseScene.h"

SceneMng *SceneMng::sInstance = nullptr;


void SceneMng::Draw(void)
{
	_dbgAddDraw();											// ÃŞÊŞ¯¸—p‚Ì•`‰æ

	// •`‰æ‚Ì‡”Ô‚Ì•À‚Ñ‘Ö‚¦
	std::sort(_drawList.begin(), _drawList.end(),
		[](DrawQueT &left, DrawQueT &right) {

		// µ°ÊŞ°×²ÄŞ‚Å1‚Â‚¸‚Â”ä‚×‚Ä‚­‚ê‚éA¡‰ñ‚ÍÚ²Ô°—Dæ‚¾‚©‚çÚ²Ô°‚©‚ç‚»‚ë‚¦‚Ä“¯‚¶Ú²Ô°‚¾‚Á‚½ê‡‚»‚±‚Å¾Ş¯Äµ°ÀŞ°‚ğ‚Í‚¶‚ß‚Ä“ü‚ê‘Ö‚¦‚é
		return std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(left), std::get<static_cast<int>(DRAW_QUE::ZODER)>(left)) 
				<
				std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(right), std::get<static_cast<int>(DRAW_QUE::ZODER)>(right));
	});

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// •`‰æÚ²Ô°‚â•`‰æÓ°ÄŞ‚Ì‰Šú’l‚ğİ’è‚·‚é
	LAYER drawLayer = begin(LAYER());
	int blendMode = DX_BLENDMODE_NOBLEND;
	int blendModeNum = 0;

	// Que‚Ì•`‰ææ‚ğİ’è
	SetDrawScreen(_layerGID);
	ClsDrawScreen();
	SetDrawBlendMode(blendMode, blendModeNum);

	// ½À¯¸‚É‚½‚Ü‚Á‚Ä‚¢‚éQue‚ğ•`‰æ‚·‚é
	for (auto dQue : _drawList)
	{

		// tie‚Éî•ñ‚ğ‚Î‚ç‚µ‚Ä‚à‚ç‚¤‚½‚ß‚Ì•Ï”‚ğì‚é
		double x, y, rad;
		int id;
		LAYER layer;

		// ‘O‚Ì·­³‚Ì“à—e‚ğŠm•Û
		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		// tie î•ñ‚ğ‚Ü‚Æ‚ß‚Äæ‚èo‚µ‚Ä‚Î‚ç‚Î‚ç‚É‚µ‚Ä‚­‚ê‚é		 ignore “Ç‚İ”ò‚Î‚µ‚Ä‚­‚ê‚é
		std::tie(id, x, y, rad, std::ignore, layer, blendMode, blendModeNum) = dQue;	// î•ñ‚ğ“ü‚ê‚é tie ‚ª‚Î‚ç‚µ‚Ä‚­‚ê‚é
		
		if ((layer != drawLayer) || (blendModeOld != blendMode) || (blendModeNumOld != blendModeNum))
		{
			// _layerGID‚É‘‚¢‚½“à—e‚ğƒoƒbƒNƒoƒbƒtƒ@‚É•`‰æ‚·‚é
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(layPos.x, layPos.y, 1.0, 0, _layerGID, true);

			// Ÿ‚ÌQue‚Ì‚½‚ß‚Ì‰Šú‰»‚µ‚ÄA•`‰ææ‚ğˆê•`‰ææ‚Éİ’è‚·‚é
			SetDrawScreen(_layerGID);
			SetDrawBlendMode(blendMode, blendModeNum);
			ClsDrawScreen();
		}

		// ’†S•`‰æ‚È‚Ì‚Å”š”­‚Ì“s‡‚ª‚¢‚¢
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

	SetDrawBlendMode(blendMode, blendModeNum);
	DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _layerGID, true);

	ScreenFlip();	// — ‰æ–Ê‚©‚ç•\‰æ–Ê‚É
}

void SceneMng::Sound(void)
{
	for (auto sQue : _soundList)
	{
		PlaySoundMem(std::get<static_cast<int>(SOUND_QUE::SOUND)>(sQue), DX_PLAYTYPE_BACK, std::get<static_cast<int>(SOUND_QUE::LOOP)>(sQue));
	}
}

SceneMng::SceneMng() :ScreenSize{ 800,600 }, GameScreenSize{ 500 , 390 }, ScreenCenter{ ScreenSize / 2 }, GameScreenOffset{ (ScreenSize - GameScreenSize) / 2 }
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

		_drawList.clear();	// —v‘f‚ğ‚·‚×‚ÄÁ‚µ‚Ä‚­‚ê‚é
		_soundList.clear();

		AddDrawQue({ IMAGE_ID("˜g")[0],400,300,0,0,LAYER::UI,DX_BLENDMODE_NOBLEND, 255 });		// ˜g‚Ì•`‰æ

		_activeScene = (*_activeScene).Update(std::move(_activeScene));							// (*)‚ğ‚Â‚¯‚é‚±‚Æ‚É‚æ‚Á‚Ä½Ï°ÄÎß²İÀ‚ÌŠÇ—‚µ‚Ä‚¢‚é’†g	->‚Å’¼ÚŒ©‚Ä‚à‚¢‚¢‚ª‚Ç‚¤‚Å‚«Šm•Û‚µ‚½‚â‚Â‚ğŒ©•ª‚¯‚é‚ª‚Ş‚¸‚­‚È‚é

		Draw();
		

		(*_activeScene).RunActQue(std::move(_actList));											// î•ñ‚ğmove‚µ‚Ä“n‚µ‚Ä‚ ‚°‚é

		Sound();

		_gameCount++;																			// ¹Ş°Ñ¶³İÄ
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
		// ‰æ‘œID‚ª•s³‚¾‚Á‚½‚Ì‚Å’Ç‰Á‚µ‚Ü‚¹‚ñ
		return false;
	}

	// Que‚ğ’Ç‰Á
	//_drawList.push_back‚ÍŒÃ‚¢ŠÂ‹«
	_drawList.emplace_back(dQue);

	return true;
}

bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);
	return true;
}

bool SceneMng::SysInit(void)
{
	SetWindowText("1916025_terasaki");

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);	//½¸Ø°İ»²½Ş

	ChangeWindowMode(true);							//ture:window false:ÌÙ½¸Ø°İ

	if (DxLib_Init() == -1)
	{
		return false;								//DX×²ÌŞ×Ø‰Šú‰»ˆ—
	}
	SetDrawScreen(DX_SCREEN_BACK);					//‚Ğ‚Æ‚Ü‚¸ÊŞ¯¸ÊŞ¯Ì§‚É•`‰æ

	// ŠeÚ²Ô°—p‚Ì½¸Ø°İ‚ğ¾¯Ä
	_layerGID = MakeScreen(ScreenSize.x, ScreenSize.y, true);

	_dbgSetup(255);									// ÃŞÊŞ¯¸Ş—p

	lpImageMng.GetID("˜g"	, "image/frame.png");		// ˜g
	lpImageMng.GetID("black", "image/black.png");		// •”Â
	lpImageMng.GetID("white", "image/white.png");		// ”’”Â



	return false;
}
