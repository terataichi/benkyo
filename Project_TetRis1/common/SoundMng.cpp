#include "SoundMng.h"
#include <DxLib.h>
#include <map>

std::unique_ptr <SoundMng, SoundMng::SoundMngDeleter> SoundMng::_sInstance(new SoundMng());


const VecInt& SoundMng::GetID(const std::string& key)
{
	return GetID(key, key);
}

const VecInt& SoundMng::GetID(const std::string& key, const std::string& fileName)
{
	// LoadSoundMem 同じキーがあるかチェックして
	if (sndMap.find(key) == sndMap.end())
	{
		sndMap[key].resize(1);
		sndMap[key][0] = LoadSoundMem(fileName.c_str());
	}

	return sndMap[key];
}

SoundMng::SoundMng()
{
}

SoundMng::~SoundMng()
{
}
