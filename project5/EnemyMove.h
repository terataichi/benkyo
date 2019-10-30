#pragma once
#include <Vector2.h>

class EnemyMove
{
public:
	EnemyMove(Vector2dbl& pos);
	~EnemyMove();
	void Update(void);
private:
	Vector2dbl& _pos;
};

