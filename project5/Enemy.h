#pragma once
#include "Obj.h"
#include "EnemyMove.h"

#define ENEMY_Y 5
#define ENEMY_X 10
#define ENEMY_MAX ENEMY_Y * ENEMY_X

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
	AIM,	// �ڕW�n�_�̏��
	MAX
};

							 // ���		���W		����		�ڕW�n�_�̏��
using EnemyState = std::tuple<ENEMY_TYPE, Vector2dbl, Vector2dbl,MoveState&>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState& state);
	void Update(sharedObj obj) override;
	~Enemy();
private:
	EnemyMove moveCtl{ _pos , _rad, _exFlag};		// ���̃N���X�ɂق��������Q�Ƃœn���Ă�����
	void init();
	ENEMY_TYPE _type;
};

