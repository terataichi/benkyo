#pragma once
#include <Vector2.h>
#include <vector>
#include "Obj.h"

enum class MOVE_TYPE
{
	WAIT,								// �҂�����
	SIGMOID,							// ���Ӳ�ދȐ�
	SPIRAL,								// ��]
	PITIN,								// �߯Ĳ�
	LR,									// ���E�ړ�
	SCALE,								// �g��k�������[��
	ATTACK								// �ˌ�
};

#define LR_GAIN 120						// ���E�ړ��̈ړ���

										// ����	 ,	�ړI�n	���i�[����
using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2dbl>>;

class EnemyMove
{
public:
	EnemyMove(Vector2dbl& pos, double& rad, bool& atFlag);
	~EnemyMove();
	const MOVE_TYPE MoveType(void)const;
	void Update(sharedObj obj);								// �X�V
	bool SetMoveState(MoveState& state, bool newFlag);		// �V������񂪗~�����Ȃ������p�t���O
	void PitInCnt(void);									// �G�̏���
	MoveState _aim;											// �ڕW�Ɋւ�����i�[

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
	void MoveAttack(void);									// �ˌ�

	int _count;												// �҂����ԂȂǂ��ڰъǗ��p

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
	int _scaleCnt;											// �ްѶ��Ă��ƍŏ�����Ďn�܂邩��V���������

	static int _pitInCnt;									// �S�����������m�F���邽�߂� 

	Vector2dbl _plPos;										// ��ڲ԰�̍��W�i�[�p

	bool& _exFlag;											// �����׸�
	
	Vector2dbl _scalePos;									// �U���I����ŏ��̽����߽����𓙔{�Ƃ��Ă݂Ăق�������						
};

