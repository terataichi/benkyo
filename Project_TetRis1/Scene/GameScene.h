#pragma once
#include <functional>
#include <vector>
#include "BaseScene.h"
#include "../Obj.h"

// �F�B�錾
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
	// --- �F�B�ꗗ ---
	friend FuncShake;
	friend Block;

	std::vector<sharedObj>_objList;
	void RunInsQue(BlockInsT& blockInsList) override;				// �����Ųݽ�ݽ����
};

