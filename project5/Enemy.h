#pragma once
#include "Obj.h"
#include "EnemyMove.h"

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

using EnemyState = std::tuple<ENEMY_TYPE, Vector2dbl, Vector2dbl>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState& state);
	void Update(void) override;
	~Enemy();
private:
	EnemyMove moveCtl{ _pos };
	void init();
	ENEMY_TYPE _type;
};

