#pragma once
#include <Scene\BaseScene.h>
#include <vector>

struct FuncShake
{
	bool operator()(ActQueT& actQue, void* scene);		// 引数を受け取って弾を出したい
};

