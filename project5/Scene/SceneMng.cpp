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

	for (auto layer : LAYER())
	{
		SetDrawScreen(_screenID[layer]);
		ClsDrawScreen();

	}
	// ｽﾀｯｸにたまっているQueを描画する
	for (auto dQue : _drawList)
	{

		// tieに情報をばらしてもらうための変数を作る
		double x, y, rad;
		int id;
		LAYER layer;
		// tie 情報をまとめて取り出してばらばらにしてくれる		 ignore 読み飛ばしてくれる
		std::tie(id, x, y, rad, std::ignore, layer) = dQue;	// 情報を入れる tie がばらしてくれる
		
		// 今のｽｸﾘｰﾝとIDが違ったらそのﾚｲﾔｰに書きこめる
		if (GetDrawScreen() != _screenID[layer])
		{
			SetDrawScreen(_screenID[layer]);
			ClsDrawScreen();
		}

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

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// 各ﾚｲﾔｰのｽｸﾘｰﾝを描画する
	for (auto layer : LAYER())
	{
		DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _screenID[layer], true);
	}

	

	ScreenFlip();	// 裏画面から表画面に
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
	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		_dbgStartDraw();

		_drawList.clear();	// 要素をすべて消してくれる
		_soundList.clear();

		AddDrawQue({ IMAGE_ID("枠")[0],400,300,0,0,LAYER::UI });		// 枠の描画

		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// (*)をつけることによってｽﾏｰﾄﾎﾟｲﾝﾀの管理している中身	->で直接見てもいいがどうでき確保したやつを見分けるがむずくなる

		Draw();
		Sound();

		(*_activeScene).RunActQue(std::move(_actList));					// 情報をmoveして渡してあげる

		_gameCount++;													// ｹﾞｰﾑｶｳﾝﾄ
	}
	// delete _activeScene;
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
		// 画像IDが不正だったので追加しません
		return false;
	}

	// Queを追加
	//_drawList.push_backは古い環境
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

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);	//ｽｸﾘｰﾝｻｲｽﾞ

	ChangeWindowMode(true);							//ture:window false:ﾌﾙｽｸﾘｰﾝ

	if (DxLib_Init() == -1)
	{
		return false;								//DXﾗｲﾌﾞﾗﾘ初期化処理
	}
	SetDrawScreen(DX_SCREEN_BACK);					//ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画

	// 各ﾚｲﾔｰ用のｽｸﾘｰﾝをｾｯﾄ
	for (auto id : LAYER())
	{
		_screenID.try_emplace(id, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	}

	_dbgSetup(255);									// ﾃﾞﾊﾞｯｸﾞ用

	lpImageMng.GetID("枠", "image/frame.png");		// 枠


	return false;
}
