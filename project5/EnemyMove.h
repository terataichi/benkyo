#pragma once
#include <Vector2.h>
#include <vector>

enum class MOVE_TYPE
{
	WAIT,								// �҂�����
	SIGMOID,							// ���Ӳ�ދȐ�
	SPIRAL,								// ��]
	PITIN,								// �߯Ĳ�
	LR,									// ���E�ړ�
	SCALE								// �g��k�������[��
};

#define PI 3.141592						// �~����
#define LR_GAIN 120						// ���E�ړ��̈ړ���

										// ����	 ,	�ړI�n	���i�[����
using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2dbl>>;

class EnemyMove
{
public:
	EnemyMove(Vector2dbl& pos , double& rad);
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
	void MoveLR(void);										// ���E�ړ�
	void MoveScale(void);									// �g��k��

	int count;

	MoveState _aim;											// �ڕW�Ɋւ�����i�[
	int _aimCnt;											// �G�̊Ǘ��p
	
	Vector2dbl _startPos;									// �e�ړ��֐��̽��Ēn�_
	Vector2dbl _endPos;										// �e�ړ��֐��̴��ޒn�_

	Vector2dbl& _pos;										// ���W���Q�ƂŎ󂯎��
	Vector2dbl _oldPos;										// �O���ڰтɂ������W�i�[
	double& _rad;											// �p�x���Q�ƂŎ󂯎���ď��������邽�߂�
	double _angle;											// �~�`��p�̊p�x
	double _angleTotal;										// �p�x�̍��v�l
	double _angleCon;										// �p�x����1��-1�������Ă�����
	Vector2dbl _lenght;										// ���@�̊p�x��ς����
	double _radius;											// ���a
	Vector2dbl _oneMoveVec;									// �P�ڰѓ�����̈ړ���
	double _moveGain;										// ���Ӳ�ޗp�̓����̕�
	Vector2dbl _scaleGain;									// �g��k���p�̕�
	static int _pitInCnt;									// �S�����������m�F���邽�߂� 
	int _p;

};

