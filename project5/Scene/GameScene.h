#pragma once
#include <functional>
#include <vector>
#include "BaseScene.h"
#include "../Obj.h"

// 友達宣言
struct FuncCheckHit;
struct FuncBullet;
struct FuncShake;


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
	friend FuncCheckHit;		
	friend FuncBullet;
	friend FuncShake;

	std::vector<sharedObj>_objList;
	void RunActQue(std::vector<ActQueT> actList) override;	// ｱﾀｯｸに必要な処理をここでやらせる

	// func用
	void InitFunc(void);
	std::map<ACT_QUE, funcAct>funcQue;

	int _shakeCount;		// 画面揺らす用

};

