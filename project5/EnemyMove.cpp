#include "EnemyMove.h"
#include <DxLib.h>

EnemyMove::EnemyMove(Vector2dbl& pos) :_pos(pos)
{

}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	int a = 30;
	_pos.x += (rand() % a);
	_pos.x -= (rand() % a);
	_pos.y += (rand() % a);
	_pos.y -= (rand() % a);

}
