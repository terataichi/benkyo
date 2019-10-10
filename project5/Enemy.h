#pragma once
#include "Obj.h"

enum class ENEMY_TYPE
{
	A,
	B,
	C,
	MAX
};

enum class ENEMY_STATE
{
	TYPE,
	VECTOR,
	SIZE,
	MAX
};

using EnemyState = std::tuple<ENEMY_STATE, ENEMY_STATE, ENEMY_STATE>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState& state);
	~Enemy();
private:
	void init();
};

