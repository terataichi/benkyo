#pragma once
#include <memory>
#include <map>
#include <tuple>
#include <vector>
#include "../common/Vector2.h"
#include "BaseScene.h"
#include "../LAYER.h"
#include "../BLOCK_TYPE.h"

enum class DRAW_QUE
{
	IMAGE,				// 画像
	X,					// 座標
	Y,
	REC_X,				// 左上の座標
	REC_Y,
	SIZE_X,				// 画像のｻｲｽﾞ
	SIZE_Y,
	ZODER,				// レイヤー内の描画順番(数値の低いほうが奥)
	LAYER,				// IDの小さいほうが奥に描画
};

//							id	x, y,左上の座標,画像ｻｲｽﾞ,奥行 
using DrawQueT = std::tuple<int, double, double, int, int, int, int, int, LAYER>;		// DRAW_QUEの内容

enum class SOUND_QUE
{
	SOUND,
	LOOP
};
//							id	ループさせるかさせないか
using SoundQueT = std::pair<int, bool>;

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:

	static SceneMng &GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	void Run(void);

	
	bool AddSoundQue(SoundQueT sQue);
	bool AddDrawQue(DrawQueT dQue);
	bool AddActQue(ActQueT aQue);
	bool AddBlockInsQue(BlockInsT bQue);

	const Vector2 ScreenSize;			// ｽｸﾘｰﾝｻｲｽﾞ
	const Vector2 ScreenCenter;			// ｽｸﾘｰﾝ中央
	const Vector2 GameScreenSize;		// ｹﾞｰﾑ画面ｻｲｽﾞ
	const Vector2 GameScreenOffset;		// ｹﾞｰﾑ画面用のオフセット
	int _gameCount;					// ﾌﾚｰﾑ管理用ｹﾞｰﾑｶｳﾝﾄ
private:

	static SceneMng* sInstance;
	unique_Base _activeScene;

	void Draw(void);					// 描画
	void Sound(void);					// ｻｳﾝﾄﾞ

	int _layerGID;

	//std::map<LAYER, int>_screenID;		// screen用の
	std::vector<SoundQueT>_soundList;		// ｻｳﾝﾄﾞﾘｽﾄ
	std::vector<DrawQueT>_drawList;			// 描画リスト
	std::vector<ActQueT>_actList;			// ｱｸｼｮﾝﾘｽﾄ
	BlockInsT _blockInsList;				// ﾌﾞﾛｯｸのｲﾝｽﾀﾝｽﾘｽﾄ

	SceneMng();							// ｺﾝｽﾄﾗｸﾀ
	~SceneMng();						// ﾃﾞｽﾄﾗｸﾀ
	bool SysInit(void);
};

