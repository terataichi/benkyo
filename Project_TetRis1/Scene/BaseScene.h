#pragma once
#include <memory>
#include <vector>
#include "../Obj.h"
#include "../common/Vector2.h"
#include "../BLOCK_TYPE.h"

class BaseScene;	//	ﾌﾟﾛﾄﾀｲﾌﾟ宣言(中身はわからないので注意)

enum class ACT_QUE
{
	NON,
	SHOT,
	CHECK_HIT,
	SHAKE,
	MAX
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;
using BlockInsT = std::pair<BLOCK_TYPE, bool>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;				// own 自身
	virtual void RunActQue(std::vector<ActQueT> actList);			// 全てのｼｰﾝで必要じゃないから純粋仮想関数にはしていない
	virtual void RunInsQue(BlockInsT& blockInsList);	// ｲﾝｽﾀﾝｽで渡してあげる

	Vector2 _screenPos;
};

