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
		return *_sInstance;	// * �ϰ��߲���̒��g��Ԃ�
	}

	// �摜�̎擾
	const VecInt& GetID(const std::string& key);
	const VecInt& GetID(const std::string& key, const std::string& fileName);
	const VecInt& GetID(const std::string& key, const std::string& fileName,
					const Vector2& divSize , const Vector2& all);


private:
	struct ImageMngDeleter	// �Ұ���Ȱ�ެ��̶�����ذ��
	{
		void operator()(ImageMng* imageMng)const
		{
			delete imageMng;
		}
	};

	ImageMng();
	~ImageMng();	// �Ұ���Ȱ�ެ�����̫����ذ��

	static std::unique_ptr<ImageMng, ImageMngDeleter>_sInstance;
	
	std::map<std::string, VecInt> imgMap;

};

