#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include <Vector2.h>
#include "BaseScene.h"

//							id	 x	 y		rect	size
using DrawQueT = std::tuple<int, int, int,Vector2, Vector2>;

#define lpSceneMng SceneMng::GetInstance()

enum class DRAW_QUE
{
	IMAGE,					// 画像ID
	X,						// X座標
	Y,						// Y座標
	Rect,					// 画像の左上指定
	SIZE,					// 画像サイズ
};

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

	std::vector<DrawQueT>_drawList;

	SceneMng();		// ｺﾝｽﾄﾗｸﾀ
	~SceneMng();	// ﾃﾞｽﾄﾗｸﾀ
	bool SysInit(void);
};

