#include "EnemyMove.h"
#include <algorithm>
#include <math.h>
#include <Vector2.h>
#include <Enemy.h>
#include "_Debug/_DebugConOut.h"
#include "_Debug/_DebugDispOut.h"
#include <Scene\SceneMng.h>

int EnemyMove::_pitInCnt;

EnemyMove::EnemyMove(Vector2dbl& pos, double& rad,bool& atFlag) :_pos(pos),_rad(rad),_exFlag(atFlag)
{
	_scaleCnt = 30;		// �g�嗦0�Ŏn�߂�������30�����ꂽ
	_move = nullptr;
	_aimCnt = -1;						// 0���Ƃ����Ȃ豸������
	_angleTotal = std::atan(0.0);		// 0�x���i�[
	_pitInCnt = 0;
}

EnemyMove::~EnemyMove()
{
}

const MOVE_TYPE EnemyMove::MoveType(void) const
{
	return _aim[_aimCnt].first;
}

void EnemyMove::Update(sharedObj obj)
{
	_plPos = (*obj).pos();
	if (_move != nullptr)					// ���g�����邩�Ȃ����`�F�b�N����
	{
		(this->*_move)();					// �D��x�����邽�߂ɂ����������Ȃ��Ƃ����Ȃ�
											// ���Ȃ���this->(*_move())�Ȃ��Ă��܂��B
	}
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

void EnemyMove::PitInCnt(void)
{
	_pitInCnt++;
}

void EnemyMove::SetMovePrg(void)
{
	
	_aimCnt++;

	// �U���̌���߯Ĳ݂��I�������g��k���ɖ߂��Ăق���
	if (_aimCnt >= static_cast<int>(_aim.size()))
	{
		auto checkAim = [&]() {
			for (_aimCnt = 0; _aimCnt < static_cast<int>(_aim.size()); _aimCnt++)
			{
				if (_aim[_aimCnt].first == MOVE_TYPE::SCALE)
				{
					return true;
				}
			}
			return false;
		};

		if (!checkAim())
		{
			return;
		}
	}

	// �A�^�b�N���I��������ɖ߂��Ăˁ[
	if (_pos.y >= lpSceneMng.GameScreenSize.y)
	{
		_pos.y = -100;
	}

	_startPos = _pos;																					// ���̈ʒu�����Ēn�_
	_endPos = _aim[_aimCnt].second;																		// �ŏI�n�_
	_count = 0;

	// first�̒���TYPE�ɂ���ē�������ς���
	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
		break;
	case MOVE_TYPE::SIGMOID:
		_moveGain = -5;																					// ���Ӳ�ނ��ォ��n�߂邽�߂�-10����ꂽ
		_oneMoveVec.x = ((_endPos.x - _startPos.x) / 90.0);												// 3�b�o�܂łɈړ�������P�ڰт̈ړ���
		_move = &EnemyMove::MoveSigmoid;
		break;
	case MOVE_TYPE::SPIRAL:
		_angle = std::atan( _startPos.y - _endPos.y );													// �����̊p�x�����߂�
		_radius = abs(_endPos.y - _startPos.y);															// ���a�̐ݒ�
		_angleCon = ((_endPos.y - _startPos.y) / abs(_endPos.y - _startPos.y)) *((lpSceneMng.ScreenCenter.x / 2 - _startPos.x) / abs(lpSceneMng.ScreenCenter.x / 2 - _startPos.x)) * -1;
		_move = &EnemyMove::MoveSpiral;
		break;
	case MOVE_TYPE::PITIN:
		if (_startPos.y > 0)
		{
			// �P��ڂ�LR�ɍ��킹����
			_endPos.x = ((_endPos.x - 60) + (((lpSceneMng._gameCount + 60) / LR_GAIN) % 2 * LR_GAIN)) + (((lpSceneMng._gameCount + 60) % LR_GAIN) * ((((lpSceneMng._gameCount + 60) / LR_GAIN) % 2) * -2 + 1));
			_lenght = _endPos - _pos;													// ���_�ɍ��킹��
			_rad = std::atan2(_lenght.y, _lenght.x) + (PI * 90.0) / 180.0;				// �p�x�𑪂�

		}
		else
		{
			// ���ڈȍ~�͊g��k���̓����ɍ��킹����
			_scaleCnt += 60;
			_endPos = _scalePos +
				_scaleGain *
				(static_cast<double>(((_scaleCnt + 100) / 2) % 30) / 100.0) *
				((static_cast<double>((((_scaleCnt + 100) / 2) / 30) % 2) * 2.0 - 1.0)) -
				(static_cast<double>((((_scaleCnt + 100) / 2) / 30) % 2) * (_scaleGain * 0.3));
		}
		_oneMoveVec = ((_endPos - _startPos) / 60.0);													// 2�b�o�܂łɈړ�������P�ڰт̈ړ���
		_move = &EnemyMove::PitIn;
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		break;
	case MOVE_TYPE::SCALE:
		_exFlag = false;
		_scaleGain = (_endPos - _scalePos);
		_move = &EnemyMove::MoveScale;
		break;
	case MOVE_TYPE::ATTACK:
		_angleTotal = 0;
		_move = &EnemyMove::MoveAttack;
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
		_moveGain += 0.12;
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
	if (_angleTotal < ((PI * (45 * 9)) / 180.0))
	{
		// ��ԍŏ��ɑO�ڰтɂ������W���i�[����
		_oldPos = _pos;

		// �ړ�
		_pos.x = (_radius * std::cos(_angle)) + _endPos.x;
		_pos.y = (_radius * std::sin(_angle)) + _endPos.y;

		// �p�x����							
		_angle += (PI * 3) / 120.0 * _angleCon;
		_angleTotal += (PI * 3) / 120.0;			// ���v���Z

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
	
	if (_count < 60)								// X��Y�������������邱�Ƃɂ���Čv�Z�ʂ�����
	{
		// �ړ��ʂ��c���Ă���ꍇ
		_pos += _oneMoveVec;

	}
	else
	{
		// �i�[���I�������؂�ւ���
		_pos = _endPos;																// �ꉞ������C������
		_rad = 0;																	// �����I�������p�x�����Ƃ̈ʒu�ɖ߂�
		_pitInCnt++;
		SetMovePrg();
	}
	_count++;
}

void EnemyMove::Wait(void)
{
	_count++;
	// �I�[�n�_�ɗ�����؂�ւ���
	if (_count > _aim[_aimCnt].second.x)
	{
		
		SetMovePrg();
	}
	
}

void EnemyMove::MoveLR(void)
{

	// ���E�ړ�
	_pos.x = ((_endPos.x - 60) + ((lpSceneMng._gameCount / LR_GAIN) % 2 * LR_GAIN)) + ((lpSceneMng._gameCount % LR_GAIN) * (((lpSceneMng._gameCount / LR_GAIN) % 2) * -2 + 1));

	// �Ō���̓z�܂ł�����ā@���@�����߽�ɂ�����
	if (_pitInCnt >= ENEMY_MAX && (_endPos.x / 100.0) == (_pos.x / 100.0))
	{
		_scalePos = _pos;
		SetMovePrg();
	}
}

void EnemyMove::MoveScale(void)
{
	// �f�o�b�N�p
	//_dbgDrawLine(lpSceneMng.GameScreenOffset.x + _startPos.x, 0, lpSceneMng.GameScreenOffset.x + _startPos.x, lpSceneMng.ScreenSize.y, 0xfffff);
	
	// �ړ�
	_pos =
		_scalePos +
		_scaleGain *
		(static_cast<double>(((_scaleCnt + 100) / 2) % 30 ) / 100.0) *
		((static_cast<double>((((_scaleCnt + 100) / 2) / 30) % 2) * 2.0 - 1.0)) -
		(static_cast<double>((((_scaleCnt + 100) / 2) / 30) % 2) * (_scaleGain * 0.3));

	if (_count >= 120)
	{
		// gameScene�����׸ނ��󂯎���Ă���
		if (_exFlag)
		{
			SetMovePrg();
			_exFlag = false;
		}
	}
	_scaleCnt++;
	_count++;

}

void EnemyMove::MoveAttack(void)
{
	if (_count < 60)
	{
		_rad += (PI * 3) / 10.0 * _angleCon;
	}
	else
	{
		_endPos = { _plPos.x , _plPos.y + 100.0 };														// ��ڲ԰��菭������ڕW�n�_�ɂ���
		_count = 0;
		_oneMoveVec = ((_endPos - _startPos) / 60.0);													// 2�b�o�܂łɈړ�������P�ڰт̈ړ���
		_lenght = _endPos - _pos;													// ���_�ɍ��킹��
		_rad = std::atan2(_lenght.y, _lenght.x) + (PI * 90.0) / 180.0;				// �p�x�𑪂�
		_move = &EnemyMove::PitIn;																		// �������߯Ĳ݂Ɠ���������end�|�X�����ς��Ă�����
	}
	_count++;
}