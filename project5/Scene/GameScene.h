#pragma once
#include <functional>
#include <vector>
#include "BaseScene.h"
#include "../Obj.h"

// �F�B�錾
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
	// --- �F�B�ꗗ ---
	friend FuncCheckHit;		
	friend FuncBullet;
	friend FuncShake;

	std::vector<sharedObj>_objList;
	void RunActQue(std::vector<ActQueT> actList) override;	// �����ɕK�v�ȏ����������ł�点��

	// func�p
	void InitFunc(void);
	std::map<ACT_QUE, funcAct>funcQue;

	int _shakeCount;		// ��ʗh�炷�p

};

