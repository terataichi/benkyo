#include "EnemyMove.h"


EnemyMove::EnemyMove(Vector2& pos) :_pos(pos)
{

}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	_pos.x++;
}
