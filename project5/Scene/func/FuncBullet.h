#pragma once
#include <Scene\BaseScene.h>

// 関数オブジェクト作るよ
struct FuncBullet
{
	bool operator()(ActQueT& actQue, std::vector<sharedObj>& objList);
};

