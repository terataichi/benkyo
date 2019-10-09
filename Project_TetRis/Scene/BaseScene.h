#pragma once
#include <memory>

class BaseScene;	//	ﾌﾟﾛﾄﾀｲﾌﾟ宣言(中身はわからないので注意)

using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;	// own 自身
};

