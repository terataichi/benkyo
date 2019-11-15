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


	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// ½À¯¸‚É‚½‚Ü‚Á‚Ä‚¢‚éQue‚ğ•`‰æ‚·‚é
	for (auto dataQue : _drawList)
	{
		
		// tie‚Éî•ñ‚ğ‚Î‚ç‚µ‚Ä‚à‚ç‚¤‚½‚ß‚Ì•Ï”‚ğì‚é
		double x, y, rad;
		int id;
		LAYER layer;
		// tie î•ñ‚ğ‚Ü‚Æ‚ß‚Äæ‚èo‚µ‚Ä‚Î‚ç‚Î‚ç‚É‚µ‚Ä‚­‚ê‚é		 ignore “Ç‚İ”ò‚Î‚µ‚Ä‚­‚ê‚é
		std::tie(id, x, y, rad, std::ignore, layer) = dataQue;	// î•ñ‚ğ“ü‚ê‚é tie ‚ª‚Î‚ç‚µ‚Ä‚­‚ê‚é
		
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
	// ²ÃÚ°À°‚Å‚â‚éê‡
	// std::vector<_dra>
	//for (auto dataQue = _drawList.begin(); dataQue != _drawList.end(); dataQue++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(*dataQue),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(*dataQue),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(*dataQue),
	//		true);
	//}

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

	for (auto layer : LAYER);
	{ }

	_screenID[LAYER::BG];

	_dbgSetup(200);									// ÃŞÊŞ¯¸Ş—p


	lpImageMng.GetID("˜g", "image/frame.png");


	return false;
}
