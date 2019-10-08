#include "ImageMng.h"
#include "Enemy.h"



Enemy::Enemy()
{
	init();
}


Enemy::~Enemy()
{

}

void Enemy::init()
{
	AnimVector data;

	data.emplace_back(lpImageMng.GetID("“G”š”­")[0],10);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[1], 15);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[2], 20);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[3], 25);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[4], 30);

	SetAnim("EDEHT",data);

}
