#pragma once
#include <Vector2.h>

class EnemyMove
{
public:
	EnemyMove(Vector2& pos);
	~EnemyMove();
	void Update(void);
private:
	Vector2& _pos;
};

