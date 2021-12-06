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
		return *_sInstance;	// * ½Ï°ÄÎß²İÀ‚Ì’†g‚ğ•Ô‚·
	}

	// ‰æ‘œ‚Ìæ“¾
	const VecInt& GetID(const std::string& key);
	const VecInt& GetID(const std::string& key, const std::string& fileName);


private:
	struct SoundMngDeleter	// ²Ò°¼ŞÏÈ°¼Ş¬°‚Ì¶½ÀÑÃŞØ°À°
	{
		void operator()(SoundMng* soundMng)const
		{
			delete soundMng;
		}
	};

	SoundMng();
	~SoundMng();	// ²Ò°¼ŞÏÈ°¼Ş¬°‚ÌÃŞÌ«ÙÄÃŞØ°À°

	static std::unique_ptr<SoundMng, SoundMngDeleter>_sInstance;

	std::map<std::string, VecInt> sndMap;
};
