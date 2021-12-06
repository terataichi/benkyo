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
		return *_sInstance;	// * ｽﾏｰﾄﾎﾟｲﾝﾀの中身を返す
	}

	// 画像の取得
	const VecInt& GetID(const std::string& key);
	const VecInt& GetID(const std::string& key, const std::string& fileName);


private:
	struct SoundMngDeleter	// ｲﾒｰｼﾞﾏﾈｰｼﾞｬｰのｶｽﾀﾑﾃﾞﾘｰﾀｰ
	{
		void operator()(SoundMng* soundMng)const
		{
			delete soundMng;
		}
	};

	SoundMng();
	~SoundMng();	// ｲﾒｰｼﾞﾏﾈｰｼﾞｬｰのﾃﾞﾌｫﾙﾄﾃﾞﾘｰﾀｰ

	static std::unique_ptr<SoundMng, SoundMngDeleter>_sInstance;

	std::map<std::string, VecInt> sndMap;
};
