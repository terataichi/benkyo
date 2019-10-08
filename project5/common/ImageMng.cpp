#include "ImageMng.h"
#include <DxLib.h>
#include <map>

std::unique_ptr <ImageMng, ImageMng::ImageMngDeleter> ImageMng::_sInstance(new ImageMng());


const VecInt& ImageMng::GetID(const std::string& key)
{
	return GetID(key, key);
}

const VecInt& ImageMng::GetID(const std::string& key, const std::string& fileName)
{
	// LoadGraph
	if (imgMap.find(key) == imgMap.end())
	{
		imgMap[key].resize(1);
		imgMap[key][0] = LoadGraph(fileName.c_str());
	}

	return imgMap[key];
}

const VecInt& ImageMng::GetID(const std::string& key, const std::string& fileName, const Vector2& divSize, const Vector2& divCnt)
{
	// LoadDivGraph
	// ファインドをするとBeginからendまで探してくれる
	if (imgMap.find(key) == imgMap.end())
	{
		//VecInt tmpData;
		//tmpData.resize(divCnt.x * divCnt.y);
		//if (LoadDivGraph(fileName.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &tmpData[0]) == 0)
		//{
		//	imgMap[key] = std::move(tmpData);
		//}
		//else
		//{
		//	return std::move(tmpData);
		//}

		imgMap[key].resize(divCnt.x * divCnt.y);
		LoadDivGraph(fileName.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &imgMap[key][0]);
	}
	
	return imgMap[key];
}

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}
