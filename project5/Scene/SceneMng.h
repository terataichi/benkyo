#pragma once
#include <memory>
#include <map>
#include <tuple>
#include <vector>
#include <Vector2.h>
#include <LAYER.h>
#include "BaseScene.h"

enum class DRAW_QUE
{
	IMAGE,				// �摜
	X,					// ���W
	Y,
	RAD,				// ��]�p
	ZODER,				// ���C���[���̕`�揇��(���l�̒Ⴂ�ق�����)
	LAYER,				// ID�̏������ق������ɕ`��
};

//							id	 x		 y		�p�x	���s screen
using DrawQueT = std::tuple<int, double, double, double, int, LAYER>;		// DRAW_QUE�̓��e

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

	const Vector2 ScreenSize;			// ��ذݻ���
	const Vector2 ScreenCenter;			// ��ذݒ���
	const Vector2 GameScreenSize;		// �ްщ�ʻ���
	const Vector2 GameScreenOffset;		// �ްщ�ʗp�̃I�t�Z�b�g
	int gameCount;					// �ڰъǗ��p�ްѶ���
private:

	static SceneMng* sInstance;
	unique_Base _activeScene;

	void Draw(void);

	std::map<LAYER, int>_screenID;		// screen�p��
	std::vector<DrawQueT>_drawList;		// �`�惊�X�g

	SceneMng();		// �ݽ�׸�
	~SceneMng();	// �޽�׸�
	bool SysInit(void);
};

