#include "EnemyMove.h"
#include <Vector2.h>
#include "_Debug/_DebugConOut.h"

EnemyMove::EnemyMove(Vector2dbl& pos, double& rad) :_pos(pos),_rad(rad)
{
	_move = nullptr;
	_aimCnt = -1;						// 0���Ƃ����Ȃ豸������
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{

	if (_move != nullptr)					// ���g�����邩�Ȃ����`�F�b�N����
	{
		(this->*_move)();					// �D��x�����邽�߂ɂ����������Ȃ��Ƃ����Ȃ�
											// ���Ȃ���this->(*_move())�Ȃ��Ă��܂��B
	}

	//int a = 30;
	//_pos.x += (rand() % a);
	//_pos.x -= (rand() % a);
	//_pos.y += (rand() % a);
	//_pos.y -= (rand() % a);

}

bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	if (newFlag)
	{
		_aim.clear();					//	�v�f��������
	}

	_aim = std::move(state);			// �����i�[����

	if (newFlag)
	{
		SetMovePrg();
	}

	return true;
}

void EnemyMove::SetMovePrg(void)
{
	_aimCnt++;
	if (_aimCnt >= _aim.size())
	{
		return;
	}

	_startPos = _pos;					// ���̈ʒu�����Ēn�_
	_endPos = _aim[_aimCnt].second;		// �ŏI�n�_

	// first�̒���TYPE�ɂ���ē�������ς���
	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
		count = 0;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		break;
	case MOVE_TYPE::PITIN:
		_oneMoveVec = abs(((_startPos - _endPos) / 120.0));
		_move = &EnemyMove::PitIn;
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		break;
	default:
		AST();
		_move = &EnemyMove::Wait;
		break;
	}

}

void EnemyMove::MoveSigmoid(void)
{
}

void EnemyMove::MoveSpiral(void)
{

}

void EnemyMove::PitIn(void)
{
	
	// �p�x��ς����
	Vector2dbl _lenght;
	
	if (abs(_endPos.x - _pos.x) >= abs(_oneMoveVec.x))								// X��Y�������������邱�Ƃɂ���Čv�Z�ʂ�����
	{
		// �ړ��ʂ��c���Ă���ꍇ
		_pos.x += _oneMoveVec.x;
		_pos.y += _oneMoveVec.y;

		// �p�x�̏���
		_lenght = _endPos - _pos;													// ���_�ɍ��킹��
		_rad = std::atan2(_lenght.y, _lenght.x) + 3.141592 * (90.0 / 180.0);		// �p�x�𑪂�
		//_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90.0);
		//_rad = std::atan2(-_pos.x + _endPos.x, -_endPos.y + _pos.y);
	}
	else
	{
		// �i�[���I�������؂�ւ���
		_pos = _endPos;																// �ꉞ������C������
		_rad = 0;																	// �����I�������p�x�����Ƃ̈ʒu�ɖ߂�
		SetMovePrg();
	}
}

void EnemyMove::Wait(void)
{
	// �I�[�n�_�ɗ�����؂�ւ���
	if (count > _aim[_aimCnt].second.x)
	{
		SetMovePrg();
	}
	count++;
}

void EnemyMove::MoveLR(void)
{

}
