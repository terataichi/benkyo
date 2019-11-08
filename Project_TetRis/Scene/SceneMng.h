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
	IMAGE,					// �摜ID
	X,						// X���W
	Y,						// Y���W
	Rect,					// �摜�̍���w��
	SIZE,					// �摜�T�C�Y
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

	SceneMng();		// �ݽ�׸�
	~SceneMng();	// �޽�׸�
	bool SysInit(void);
};

