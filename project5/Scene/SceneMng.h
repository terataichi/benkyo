#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include <Vector2.h>
#include "BaseScene.h"

enum class DRAW_QUE
{
	IMAGE,				// ‰æ‘œ
	X,					// À•W
	Y,
	RAD,				// ‰ñ“]Šp
	ZODER,				// ƒŒƒCƒ„[“à‚Ì•`‰æ‡”Ô(”’l‚Ì’á‚¢‚Ù‚¤‚ª‰œ)
	LAYER,				// ID‚Ì¬‚³‚¢‚Ù‚¤‚ª‰œ‚É•`‰æ
};

// ID‚Ì¬‚³‚¢‚Ù‚¤‚ª‰œ‚É•`‰æ
enum class LAYER
{
	BG,
	CHAR,
	UI,
};

//							id	 x		 y		Šp“x	‰œs screen
using DrawQueT = std::tuple<int, double, double, double, int, LAYER>;		// DRAW_QUE‚Ì“à—e

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

	std::vector<DrawQueT>_drawList;

	SceneMng();		// ºİ½Ä×¸À
	~SceneMng();	// ÃŞ½Ä×¸À
	bool SysInit(void);
};

