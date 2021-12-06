#pragma once
#include<memory>
#include <map>
#include <vector>
#include <string>
#include "Vector2.h"

using VecInt = std::vector<int>;

#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(KEY) (ImageMng::GetInstance().GetID(KEY))

class ImageMng
{
public:
	static ImageMng &GetInstance(void)
	{
		return *_sInstance;	// * ｽﾏｰﾄﾎﾟｲﾝﾀの中身を返す
	}

	// 画像の取得
	const VecInt& GetID(const std::string& key);
	const VecInt& GetID(const std::string& key, const std::string& fileName);
	const VecInt& GetID(const std::string& key, const std::string& fileName,
					const Vector2& divSize , const Vector2& all);


private:
	struct ImageMngDeleter	// ｲﾒｰｼﾞﾏﾈｰｼﾞｬｰのｶｽﾀﾑﾃﾞﾘｰﾀｰ
	{
		void operator()(ImageMng* imageMng)const
		{
			delete imageMng;
		}
	};

	ImageMng();
	~ImageMng();	// ｲﾒｰｼﾞﾏﾈｰｼﾞｬｰのﾃﾞﾌｫﾙﾄﾃﾞﾘｰﾀｰ
	
	static std::unique_ptr<ImageMng, ImageMngDeleter>_sInstance;
	
	std::map<std::string, VecInt> imgMap;

};

