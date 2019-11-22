#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;	//	ﾌﾟﾛﾄﾀｲﾌﾟ宣言(中身はわからないので注意)

enum class ACT_QUE
{
	NON,
	SHOT
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;	// own 自身
	virtual void RunActQue(std::vector<ActQueT> actList);	// 全てのｼｰﾝで必要じゃないから純粋仮想関数にはしていない
};

