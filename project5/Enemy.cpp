#include "ImageMng.h"
#include "Enemy.h"
#include <Obj.h>
#include <Scene\SceneMng.h>

Enemy::Enemy()
{
	_type = ENEMY_TYPE::A;
	init();
}

Enemy::Enemy(EnemyState & state)
{
	_unitID = UNIT_ID::ENEMY;
	_type = std::move(std::get<static_cast<int>(ENEMY_STATE::TYPE)>(state));
	_pos = std::get<static_cast<int>(ENEMY_STATE::VECTOR)>(state);
	_size = std::move(std::get<static_cast<int>(ENEMY_STATE::SIZE)>(state));
	moveCtl.SetMoveState(std::get<static_cast<int>(ENEMY_STATE::AIM)>(state), true);
	init();
}

void Enemy::Update(sharedObj obj)
{
	if (DestroyPrpc())
	{
		return;
	}
	moveCtl.Update(obj);		// ´ÈĞ°‚Ì±¯ÌßÃŞ°Ä
}

Enemy::~Enemy()
{
	moveCtl.PitInCnt();
}

bool Enemy::SetAlive(bool alive)
{
	if (!alive)
	{
		// ‚ä‚ç‚·que‚ğ“Š‚°‚é
		lpSceneMng.AddActQue({ ACT_QUE::SHAKE,*this });
	}
	
	return Obj::SetAlive(alive);
}

void Enemy::init()
{
	AnimVector data;

	data.emplace_back(lpImageMng.GetID("·¬×")[10 + 10 * static_cast<int>(_type)], 30);
	data.emplace_back(lpImageMng.GetID("·¬×")[11 + 10 * static_cast<int>(_type)], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(lpImageMng.GetID("“G”š”­")[0], 10);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[1], 15);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[2], 20);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[3], 25);
	data.emplace_back(lpImageMng.GetID("“G”š”­")[4], 30);
	data.emplace_back(-1, 35);
	SetAnim(STATE::DETH,data);

	// key‚Ìİ’è
	state(STATE::NORMAL);
	
}