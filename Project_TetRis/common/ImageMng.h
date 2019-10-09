#pragma once
#include<memory>
#include <map>
#include <vector>
#include <common\Vector2.h>

using VecInt = std::vector<int>;

#define lpImageMng ImageMng::GetInstance()

class ImageMng
{
public:
	static ImageMng &GetInstance(void)
	{
		return *_sInstance;	// * ½Ï°ÄÎß²İÀ‚Ì’†g‚ğ•Ô‚·
	}

	// ‰æ‘œ‚Ìæ“¾
	const VecInt& GetID(const std::string& key);
	const VecInt& GetID(const std::string& key, const std::string& fileName);
	const VecInt& GetID(const std::string& key, const std::string& fileName,
					const Vector2& divSize , const Vector2& all);


private:
	struct ImageMngDeleter	// ²Ò°¼ŞÏÈ°¼Ş¬°‚Ì¶½ÀÑÃŞØ°À°
	{
		void operator()(ImageMng* imageMng)const
		{
			delete imageMng;
		}
	};

	ImageMng();
	~ImageMng();	// ²Ò°¼ŞÏÈ°¼Ş¬°‚ÌÃŞÌ«ÙÄÃŞØ°À°

	static std::unique_ptr<ImageMng, ImageMngDeleter>_sInstance;
	
	std::map<std::string, VecInt> imgMap;

};

