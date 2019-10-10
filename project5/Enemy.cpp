#include "ImageMng.h"
#include "Enemy.h"
#include <Obj.h>


Enemy::Enemy()
{
	init();
}

Enemy::Enemy(EnemyState & state)
{
	_pos = std::get<static_cast<int>(ENEMY_STATE::VECTOR)>(state);
	_size = std::get<static_cast<int>(ENEMY_STATE::SIZE)>(state);
	_type = std::get<static_cast<int>(ENEMY_STATE::TYPE)>(state);

	init();
}




Enemy::~Enemy()
{

}

void Enemy::init()
{
	AnimVector data;

	data.emplace_back(lpImageMng.GetID("·¬×")[10], 30);
	data.emplace_back(lpImageMng.GetID("·¬×")[11], 60);
	SetAnim("NORMAL", data);

	data.emplace_back(lpImageMng.GetID("“G”š”­")[0], 10);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[1], 15);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[2], 20);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[3], 25);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[4], 30);
	data.emplace_back(-1, 35);
	SetAnim("DEHT",data);

	// key‚Ìİ’è
	animKey("NORMAL");
	
}
