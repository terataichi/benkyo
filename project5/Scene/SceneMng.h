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
	DRAW_MODE,			// �`��Ӱ��
	DRAW_NUM,			// Ӱ��Ɠn���l
};

//							id	x, y,�p�x,���s screen	�`��Ӱ�� �`��Ӱ�ނɓn���l
using DrawQueT = std::tuple<int, double, double, double, int, LAYER, int, int>;		// DRAW_QUE�̓��e

enum class SOUND_QUE
{
	SOUND,
	LOOP
};
//							id	���[�v�����邩�����Ȃ���
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

	const Vector2 ScreenSize;			// ��ذݻ���
	const Vector2 ScreenCenter;			// ��ذݒ���
	const Vector2 GameScreenSize;		// �ްщ�ʻ���
	const Vector2 GameScreenOffset;		// �ްщ�ʗp�̃I�t�Z�b�g
	int _gameCount;					// �ڰъǗ��p�ްѶ���
private:

	static SceneMng* sInstance;
	unique_Base _activeScene;

	void Draw(void);					// �`��
	void Sound(void);					// �����

	int _layerGID;
	//std::map<LAYER, int>_screenID;	// screen�p��
	std::vector<SoundQueT>_soundList;	// �����ؽ�
	std::vector<DrawQueT>_drawList;		// �`�惊�X�g
	std::vector<ActQueT>_actList;		// �����ؽ�

	SceneMng();							// �ݽ�׸�
	~SceneMng();						// �޽�׸�
	bool SysInit(void);
};

