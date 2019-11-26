#pragma once
#include "Obj.h"
#include <memory>
#include <Input\InputState.h>

class Player :
	public Obj
{
public:
	Player();
	Player(Vector2dbl pos, Vector2dbl size);
	void Update(sharedObj obj) override;
	~Player();

private:
	void init(void);
	std::shared_ptr<InputState> _input;				// key�̊Ǘ�

};

