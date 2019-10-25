#pragma once
#include "Obj.h"
#include <memory>
#include <Input\InputState.h>

class Player :
	public Obj
{
public:
	Player();
	Player(Vector2 pos, Vector2 size);
	void Update(void) override;
	~Player();

private:
	void init(void);
	std::shared_ptr<InputState> _input;				// key‚ÌŠÇ—
};

