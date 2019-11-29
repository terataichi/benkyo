#pragma once
#include <functional>
#include <vector>
#include "BaseScene.h"
#include "Obj.h"


using funcAct = std::function<bool(ActQueT&, std::vector<sharedObj>&)>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;
private:
	std::vector<sharedObj>_objList;
	void RunActQue(std::vector<ActQueT> actList) override;	// ±À¯¸‚É•K—v‚Èˆ—‚ğ‚±‚±‚Å‚â‚ç‚¹‚é

	void InitFunc(void);
	std::map<ACT_QUE, funcAct>funcQue;

};

