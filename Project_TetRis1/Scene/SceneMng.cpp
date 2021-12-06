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
	_dbgAddDraw();											// ﾃﾞﾊﾞｯｸ用の描画

	// 描画の順番の並び替え
	std::sort(_drawList.begin(), _drawList.end(),
		[](DrawQueT &left, DrawQueT &right) {

		// ｵｰﾊﾞｰﾗｲﾄﾞで1つずつ比べてくれる、今回はﾚｲﾔｰ優先だからﾚｲﾔｰからそろえて同じﾚｲﾔｰだった場合そこでｾﾞｯﾄｵｰﾀﾞｰをはじめて入れ替える
		return std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(left), std::get<static_cast<int>(DRAW_QUE::ZODER)>(left)) 
				>
				std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(right), std::get<static_cast<int>(DRAW_QUE::ZODER)>(right));
	});

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// 描画ﾚｲﾔｰや描画ﾓｰﾄﾞの初期値を設定する
	LAYER drawLayer = begin(LAYER());
	int blendMode = DX_BLENDMODE_NOBLEND;
	int blendModeNum = 0;

	// Queの描画先を設定
	SetDrawScreen(_layerGID);
	ClsDrawScreen();
	SetDrawBlendMode(blendMode, blendModeNum);

	// ｽﾀｯｸにたまっているQueを描画する
	for (auto dQue : _drawList)
	{

		// tieに情報をばらしてもらうための変数を作る
		Vector2dbl pos;
		Vector2 upLeftPos, size;
		int id;
		LAYER layer;

		// 前のｷｭｳの内容を確保
		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		// tie 情報をまとめて取り出してばらばらにしてくれる		 ignore 読み飛ばしてくれる
		std::tie(id, pos.x, pos.y, upLeftPos.x, upLeftPos.y, size.x, size.y, std::ignore, layer) = dQue;	// 情報を入れる tie がばらしてくれる
		
		if ((layer != drawLayer) || (blendModeOld != blendMode) || (blendModeNumOld != blendModeNum))
		{
			// _layerGIDに書いた内容をバックバッファに描画する
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(layPos.x, layPos.y, 1.0, 0, _layerGID, true);

			// 次のQueのための初期化して、描画先を一時描画先に設定する
			SetDrawScreen(_layerGID);
			SetDrawBlendMode(blendMode, blendModeNum);
			ClsDrawScreen();
		}

		// 中心描画なので爆発の都合がいい
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

	ScreenFlip();	// 裏画面から表画面に
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

		_drawList.clear();	// 要素をすべて消してくれる
		_soundList.clear();

		_activeScene = (*_activeScene).Update(std::move(_activeScene));							// (*)をつけることによってｽﾏｰﾄﾎﾟｲﾝﾀの管理している中身	->で直接見てもいいがどうでき確保したやつを見分けるがむずくなる

		Draw();

		(*_activeScene).RunActQue(std::move(_actList));											// 情報をmoveして渡してあげる


		(*_activeScene).RunInsQue(_blockInsList);

		Sound();

		_gameCount++;																			// ｹﾞｰﾑｶｳﾝﾄ
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

bool SceneMng::AddBlockInsQue(BlockInsT bQue)
{
	_blockInsList = bQue;
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
	_layerGID = MakeScreen(ScreenSize.x, ScreenSize.y, true);

	_dbgSetup(255);									// ﾃﾞﾊﾞｯｸﾞ用

	return false;
}
