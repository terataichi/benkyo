#pragma once
#include "Obj.h"



class Player :
	public Obj
{
public:
	Player();
	~Player();
private:
	void init(void);
};

