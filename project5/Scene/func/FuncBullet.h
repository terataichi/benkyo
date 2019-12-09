#pragma once
#include <Scene\BaseScene.h>
#include <vector>

// 関数オブジェクト作るよ
struct FuncBullet
{
	bool operator()(ActQueT& actQue, void* scene);		// 引数を受け取って弾を出したい
private:
	static std::map<UNIT_ID, int> _MaxCount;								// 弾の最大数の設定
};

