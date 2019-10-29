#include "ImageMng.h"
#include "Enemy.h"
#include <Obj.h>


Enemy::Enemy()
{
	_type = ENEMY_TYPE::A;
	init();
}

Enemy::Enemy(EnemyState & state)
{
	_type = std::move(std::get<static_cast<int>(ENEMY_STATE::TYPE)>(state));
	_pos = std::get<static_cast<int>(ENEMY_STATE::VECTOR)>(state);
	_size = std::move(std::get<static_cast<int>(ENEMY_STATE::SIZE)>(state));

	init();
}

void Enemy::Update(void)
{
	if (DestroyPrpc())
	{
		return;
	}
	moveCtl.Update();

	//if (rand() % 300 == 1)
	//{
	//	SetAlive(false);
	//}

}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	AnimVector data;

	data.emplace_back(lpImageMng.GetID("·¬×")[10 + 10 * static_cast<int>(_type)], 30);
	data.emplace_back(lpImageMng.GetID("·¬×")[11 + 10 * static_cast<int>(_type)], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(lpImageMng.GetID("G­")[0], 10);
	data.emplace_back(lpImageMng.GetID("G­")[1], 15);
	data.emplace_back(lpImageMng.GetID("G­")[2], 20);
	data.emplace_back(lpImageMng.GetID("G­")[3], 25);
	data.emplace_back(lpImageMng.GetID("G­")[4], 30);
	data.emplace_back(-1, 35);
	SetAnim(STATE::DETH,data);

	// keyÌÝè
	state(STATE::NORMAL);
	
}