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
	_dbgAddDraw();											// ÃŞÊŞ¯¸—p‚Ì•`‰æ

	// •`‰æ‚Ì‡”Ô‚Ì•À‚Ñ‘Ö‚¦
	std::sort(_drawList.begin(), _drawList.end(),
		[](DrawQueT &left, DrawQueT &right) {

		// µ°ÊŞ°×²ÄŞ‚Å1‚Â‚¸‚Â”ä‚×‚Ä‚­‚ê‚éA¡‰ñ‚ÍÚ²Ô°—Dæ‚¾‚©‚çÚ²Ô°‚©‚ç‚»‚ë‚¦‚Ä“¯‚¶Ú²Ô°‚¾‚Á‚½ê‡‚»‚±‚Å¾Ş¯Äµ°ÀŞ°‚ğ‚Í‚¶‚ß‚Ä“ü‚ê‘Ö‚¦‚é
		return std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(left), std::get<static_cast<int>(DRAW_QUE::ZODER)>(left)) 
				<
				std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(right), std::get<static_cast<int>(DRAW_QUE::ZODER)>(right));
	});

	for (auto layer : LAYER())
	{
		SetDrawScreen(_screenID[layer]);
		ClsDrawScreen();

	}
	// ½À¯¸‚É‚½‚Ü‚Á‚Ä‚¢‚éQue‚ğ•`‰æ‚·‚é
	for (auto dQue : _drawList)
	{

		// tie‚Éî•ñ‚ğ‚Î‚ç‚µ‚Ä‚à‚ç‚¤‚½‚ß‚Ì•Ï”‚ğì‚é
		double x, y, rad;
		int id;
		LAYER layer;
		// tie î•ñ‚ğ‚Ü‚Æ‚ß‚Äæ‚èo‚µ‚Ä‚Î‚ç‚Î‚ç‚É‚µ‚Ä‚­‚ê‚é		 ignore “Ç‚İ”ò‚Î‚µ‚Ä‚­‚ê‚é
		std::tie(id, x, y, rad, std::ignore, layer) = dQue;	// î•ñ‚ğ“ü‚ê‚é tie ‚ª‚Î‚ç‚µ‚Ä‚­‚ê‚é
		
		// ¡‚Ì½¸Ø°İ‚ÆID‚ªˆá‚Á‚½‚ç‚»‚ÌÚ²Ô°‚É‘‚«‚±‚ß‚é
		if (GetDrawScreen() != _screenID[layer])
		{
			SetDrawScreen(_screenID[layer]);
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
	ClsDrawScreen();

	// ŠeÚ²Ô°‚Ì½¸Ø°İ‚ğ•`‰æ‚·‚é
	for (auto layer : LAYER())
	{
		DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _screenID[layer], true);
	}

	ScreenFlip();	// — ‰æ–Ê‚©‚ç•\‰æ–Ê‚É
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

		_drawList.clear();	// —v‘f‚ğ‚·‚×‚ÄÁ‚µ‚Ä‚­‚ê‚é
		
		AddDrawQue({ IMAGE_ID("˜g")[0],400,300,0,0,LAYER::UI });		// ˜g‚Ì•`‰æ

		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// (*)‚ğ‚Â‚¯‚é‚±‚Æ‚É‚æ‚Á‚Ä½Ï°ÄÎß²İÀ‚ÌŠÇ—‚µ‚Ä‚¢‚é’†g	->‚Å’¼ÚŒ©‚Ä‚à‚¢‚¢‚ª‚Ç‚¤‚Å‚«Šm•Û‚µ‚½‚â‚Â‚ğŒ©•ª‚¯‚é‚ª‚Ş‚¸‚­‚È‚é
		Draw();

	}
	// delete _activeScene;
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
	for (auto id : LAYER())
	{
		_screenID.try_emplace(id, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	}

	_dbgSetup(255);									// ÃŞÊŞ¯¸Ş—p

	lpImageMng.GetID("˜g", "image/frame.png");		// ˜g


	return false;
}
