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

	_dbgAddDraw();											// ﾃﾞﾊﾞｯｸ用の描画

	// 描画の順番の並び替え
	std::sort(_drawList.begin(), _drawList.end(),
		[](DrawQueT &left, DrawQueT &right) {

		// ｵｰﾊﾞｰﾗｲﾄﾞで1つずつ比べてくれる、今回はﾚｲﾔｰ優先だからﾚｲﾔｰからそろえて同じﾚｲﾔｰだった場合そこでｾﾞｯﾄｵｰﾀﾞｰをはじめて入れ替える
		return std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(left), std::get<static_cast<int>(DRAW_QUE::ZODER)>(left)) 
				<
				std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(right), std::get<static_cast<int>(DRAW_QUE::ZODER)>(right));
	});


	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// ｽﾀｯｸにたまっているQueを描画する
	for (auto dataQue : _drawList)
	{
		
		// tieに情報をばらしてもらうための変数を作る
		double x, y, rad;
		int id;
		LAYER layer;
		// tie 情報をまとめて取り出してばらばらにしてくれる		 ignore 読み飛ばしてくれる
		std::tie(id, x, y, rad, std::ignore, layer) = dataQue;	// 情報を入れる tie がばらしてくれる
		
		// 中心描画なので爆発の都合がいい
		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true
		);

	}
	// ｲﾃﾚｰﾀｰでやる場合
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

		_drawList.clear();	// 要素をすべて消してくれる
		
		AddDrawQue({ IMAGE_ID("枠")[0],400,300,0,0,LAYER::UI });		// 枠の描画

		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// (*)をつけることによってｽﾏｰﾄﾎﾟｲﾝﾀの管理している中身	->で直接見てもいいがどうでき確保したやつを見分けるがむずくなる
		Draw();

	}
	// delete _activeScene;
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		// 画像IDが不正だったので追加しません
		return false;
	}

	// Queを追加
	//_drawList.push_backは古い環境
	_drawList.emplace_back(dQue);

	return true;
}

bool SceneMng::SysInit(void)
{
	SetWindowText("1916025_terasaki");

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);	//ｽｸﾘｰﾝｻｲｽﾞ

	ChangeWindowMode(true);							//ture:window false:ﾌﾙｽｸﾘｰﾝ

	if (DxLib_Init() == -1)
	{
		return false;								//DXﾗｲﾌﾞﾗﾘ初期化処理
	}
	SetDrawScreen(DX_SCREEN_BACK);					//ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画

	for (auto layer : LAYER);
	{ }

	_screenID[LAYER::BG];

	_dbgSetup(200);									// ﾃﾞﾊﾞｯｸﾞ用


	lpImageMng.GetID("枠", "image/frame.png");


	return false;
}
