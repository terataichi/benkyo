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

	// ｽﾀｯｸにたまっているQueを描画する
	for (auto dataQue : _drawList)
	{
		// 中心描画なので爆発の都合がいい
		DrawRotaGraph(
			std::get<static_cast<int>(DRAW_QUE::X)>(dataQue),
			std::get<static_cast<int>(DRAW_QUE::Y)>(dataQue),
			1.0,
			std::get<static_cast<int>(DRAW_QUE::RAD)>(dataQue),
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dataQue),
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
	
	// い　つ　も　の
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
		_drawList.clear();	// 要素をすべて消してくれる
		
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
	
	return false;
}
