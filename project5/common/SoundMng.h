#pragma once
#include<memory>
#include <map>
#include <vector>
#include <string>
#include "../common/Vector2.h"

using VecInt = std::vector<int>;

#define lpSoundMng SoundMng::GetInstance()
#define SOUND_ID(KEY) (SoundMng::GetInstance().GetID(KEY))

class SoundMng
{
public:
	static SoundMng &GetInstance(void)
	{
		return *_sInstance;	// * �ϰ��߲���̒��g��Ԃ�
	}

	// �摜�̎擾
	const VecInt& GetID(const std::string& key);
	const VecInt& GetID(const std::string& key, const std::string& fileName);


private:
	struct SoundMngDeleter	// �Ұ���Ȱ�ެ��̶�����ذ��
	{
		void operator()(SoundMng* soundMng)const
		{
			delete soundMng;
		}
	};

	SoundMng();
	~SoundMng();	// �Ұ���Ȱ�ެ�����̫����ذ��

	static std::unique_ptr<SoundMng, SoundMngDeleter>_sInstance;

	std::map<std::string, VecInt> sndMap;
};
