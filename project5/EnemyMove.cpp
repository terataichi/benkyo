#include "EnemyMove.h"
#include "_Debug/_DebugConOut.h"

EnemyMove::EnemyMove(Vector2dbl& pos) :_pos(pos)
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
		// �ǂ��Ɋi�[����̂����߂�
		_aim[_aimCnt].second.x = 50 + ();
		_aim[_aimCnt].second.y = (35 * 7) + ();
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
	// �ړ�


	// �i�[���I�������؂�ւ���
	if (_pos == _endPos)
	{
		SetMovePrg();
	}
}

void EnemyMove::Wait(void)
{
	count++;
	// �I�[�n�_�ɗ�����؂�ւ���
	if (count > _aim[_aimCnt].second.x)
	{
		SetMovePrg();
	}
}

void EnemyMove::MoveLR(void)
{

}
