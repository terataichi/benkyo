#pragma once
#include <memory>
#include <map>
#include <tuple>
#include <vector>
#include <Vector2.h>
#include "BaseScene.h"

enum class DRAW_QUE
{
	IMAGE,				// 画像
	X,					// 座標
	Y,
	RAD,				// 回転角
	ZODER,				// レイヤー内の描画順番(数値の低いほうが奥)
	LAYER,				// IDの小さいほうが奥に描画
};

// IDの小さいほうが奥に描画
enum class LAYER
{
	BG,
	CHAR,
	UI,
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER& key);

//							id	 x		 y		角度	奥行 screen
using DrawQueT = std::tuple<int, double, double, double, int, LAYER>;		// DRAW_QUEの内容

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

	

	bool AddDrawQue(DrawQueT dQue);

	const Vector2 ScreenSize;

private:

	static SceneMng* sInstance;
	unique_Base _activeScene;

	void Draw(void);

	std::map<LAYER, int>_screenID;		// screen用の
	std::vector<DrawQueT>_drawList;		// 描画リスト

	SceneMng();		// ｺﾝｽﾄﾗｸﾀ
	~SceneMng();	// ﾃﾞｽﾄﾗｸﾀ
	bool SysInit(void);
};

