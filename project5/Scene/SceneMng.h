#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include <Vector2.h>
#include "BaseScene.h"

//							id	 x		 y		 ‰ñ“]Šp“x
using DrawQueT = std::tuple<int, double, double, double>;

#define lpSceneMng SceneMng::GetInstance()

enum class DRAW_QUE
{
	IMAGE,
	X,
	Y,
	RAD
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

	SceneMng();		// ºÝ½Ä×¸À
	~SceneMng();	// ÃÞ½Ä×¸À
	bool SysInit(void);
};

