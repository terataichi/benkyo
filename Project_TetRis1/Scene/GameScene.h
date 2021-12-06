#pragma once
#include <functional>
#include <vector>
#include "BaseScene.h"
#include "../Obj.h"

// 友達宣言
struct FuncShake;
class Block;

using funcAct = std::function<bool(ActQueT&, void*)>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;
private:
	// --- 友達一覧 ---
	friend FuncShake;
	friend Block;

	std::vector<sharedObj>_objList;
	void RunInsQue(BlockInsT& blockInsList) override;				// ここでｲﾝｽﾀﾝｽする
};

