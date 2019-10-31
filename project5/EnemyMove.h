#pragma once
#include <Vector2.h>
#include <vector>

enum class MOVE_TYPE
{
	WAIT,
	SIGMOID,
	SPIRAL,
	PITIN,
	LR,
};

using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2dbl>>;

class EnemyMove
{
public:
	EnemyMove(Vector2dbl& pos );
	~EnemyMove();
	void Update(void);										// �X�V
	bool SetMoveState(MoveState& state, bool newFlag);		// �V������񂪗~�����Ȃ������p�t���O

private:
	void SetMovePrg(void);									// _aim�̒��̏���Ă���

	// ���ް�֐��߲���
	void (EnemyMove::*_move)(void);							// ���ް�֐��߲����i�[�p
	void MoveSigmoid(void);									// ���Ӳ�ދȐ��p
	void MoveSpiral(void);									// ��߲��
	void PitIn(void);										// �z�u
	void Wait(void);										// �҂�����
	void MoveLR(void);						

	MoveState _aim;											// �ڕW�Ɋւ�����i�[
	int _aimCnt;											// 
	
	Vector2dbl _startPos;									// �e�ړ��֐��̽��Ēn�_
	Vector2dbl _endPos;										// �e�ړ��֐��̴��ޒn�_

	Vector2dbl& _pos;

};

