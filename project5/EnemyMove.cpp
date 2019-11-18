#include "EnemyMove.h"
#include <math.h>
#include <Vector2.h>
#include "_Debug/_DebugConOut.h"
#include "_Debug/_DebugDispOut.h"
#include <Scene\SceneMng.h>

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

	// ���ޯ�ޗp
	_dbgDrawPixel(lpSceneMng.GameScreenOffset.x +  _pos.x, lpSceneMng.GameScreenOffset.y + _pos.y, 0xffffff);
	_dbgDrawLine(lpSceneMng.ScreenCenter.x, 0 ,lpSceneMng.ScreenCenter.x, lpSceneMng.ScreenSize.y, 0xfffff);
	//_dbgDrawBox(_pos.x - 15, _pos.y - 15, _pos.x + 15, _pos.y + 15, 0xffffff, false);
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
	if (_aimCnt >= static_cast<int>(_aim.size()))
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
		_moveGain = -10;																				// ���Ӳ�ނ��ォ��n�߂邽�߂�-10����ꂽ
		_oneMoveVec.x = ((_endPos.x - _startPos.x) / 180.0);											// 3�b�o�܂łɈړ�������P�ڰт̈ړ���
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		_angle = std::atan( _startPos.y - _endPos.y );													// �����̊p�x�����߂�
		_radius = abs(_endPos.y - _startPos.y);															// ���a�̐ݒ�
		_angleCon = (((_endPos.y - _startPos.y) / abs(_endPos.y - _startPos.y)) *(((lpSceneMng.ScreenCenter.x / 2 - _startPos.x) / abs(lpSceneMng.ScreenCenter.x / 2 - _startPos.x))) * -1);
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		_oneMoveVec = ((_endPos - _startPos) / 120.0);													// 2�b�o�܂łɈړ�������P�ڰт̈ړ���
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
	// �ŏI�n�_�̏ꏊ������
	if (abs(_endPos.x - _pos.x) >= abs(_oneMoveVec.x))
	{
		// ��ԍŏ��ɑO�ڰтɂ������W���i�[����
		_oldPos = _pos;

		// ���Ӳ�ފ֐�
		_pos.y = ((1.0 / (1.0 + exp(-_moveGain))) * (_endPos.y - _startPos.y)) + _startPos.y;

		// X�ړ�
		_pos.x += _oneMoveVec.x;

		// ���̍��W�ƑO�̍��W�Ŋp�x���v�Z����
		_lenght = _pos - _oldPos;
		_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90);

		// ����ς���
		_moveGain += 0.1;
	}
	else
	{
		_pos = _endPos;																// �ꉞ������C������
		SetMovePrg();
	}
}

void EnemyMove::MoveSpiral(void)
{

	// �I������
	if (_radius >= 0)
	{
		// ��ԍŏ��ɑO�ڰтɂ������W���i�[����
		_oldPos = _pos;


		// �ړ�
		_pos.x = (_radius * std::cos(_angle)) + _endPos.x;
		_pos.y = (_radius * std::sin(_angle)) + _endPos.y;

		// �p�x����							
		_angle += std::atan(0.03) * _angleCon;

		// ���a����������
		_radius -= 0.2;

		// ���̍��W�ƑO�̍��W�Ŋp�x���v�Z����
		_lenght = _pos - _oldPos;
		_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90);

	}
	else
	{
		SetMovePrg();
	}

}

void EnemyMove::PitIn(void)
{
	
	if (abs(_endPos - _pos) >= abs(_oneMoveVec))								// X��Y�������������邱�Ƃɂ���Čv�Z�ʂ�����
	{
		// �ړ��ʂ��c���Ă���ꍇ
		_pos += _oneMoveVec;

		// �p�x�̏���
		_lenght = _endPos - _pos;													// ���_�ɍ��킹��
		_rad = std::atan2(_lenght.y, _lenght.x) + (3.141592 * 90.0 )/ 180.0;		// �p�x�𑪂�
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
	// ��ԍŏ��ɑO�ڰтɂ������W���i�[����
	_oldPos = _pos;

	_pos.x -= 5;
	// ���̍��W�ƑO�̍��W�Ŋp�x���v�Z����
	_lenght = _pos - _oldPos;
	_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90);

	
}
