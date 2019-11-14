#include "EnemyMove.h"
#include <math.h>
#include <Vector2.h>
#include "_Debug/_DebugConOut.h"
#include "_Debug/_DebugDispOut.h"

EnemyMove::EnemyMove(Vector2dbl& pos, double& rad) :_pos(pos),_rad(rad)
{
	_move = nullptr;
	_aimCnt = -1;						// 0‚¾‚Æ‚¢‚«‚È‚è±¸¾½‚·‚é
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{

	if (_move != nullptr)					// ’†g‚ª‚ ‚é‚©‚È‚¢‚©ƒ`ƒFƒbƒN‚·‚é
	{
		(this->*_move)();					// —Dæ“x‚ð‚Â‚¯‚é‚½‚ß‚É‚©‚Á‚±‚ð‚Â‚¯‚È‚¢‚Æ‚¢‚¯‚È‚¢
											// ‚Â‚¯‚È‚¢‚Æthis->(*_move())‚È‚Á‚Ä‚µ‚Ü‚¤B
	}

	// ÃÞÊÞ¯¸Þ—p
	_dbgDrawPixel(_pos.x, _pos.y, 0xffffff);
	//_dbgDrawBox(_pos.x - 15, _pos.y - 15, _pos.x + 15, _pos.y + 15, 0xffffff, false);
}

bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	if (newFlag)
	{
		_aim.clear();					//	—v‘f‚ðÁ‚·‚æ
	}

	_aim = std::move(state);			// î•ñ‚ðŠi”[‚·‚é

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

	_startPos = _pos;					// ¡‚ÌˆÊ’u‚ª½À°Ä’n“_
	_endPos = _aim[_aimCnt].second;		// ÅI’n“_

	// first‚Ì’†‚ÌTYPE‚É‚æ‚Á‚Ä“®‚«•û‚ð•Ï‚¦‚é
	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
		count = 0;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		_moveGain = -10;																				// ¼¸ÞÓ²ÄÞ‚ðã‚©‚çŽn‚ß‚é‚½‚ß‚É-10‚ð“ü‚ê‚½
		_oneMoveVec.x = ((_endPos.x - _startPos.x) / 180.0);											// 3•bŒo‚Â‚Ü‚Å‚ÉˆÚ“®‚³‚¹‚é‚PÌÚ°Ñ‚ÌˆÚ“®—Ê
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		_angle = std::atan( _startPos.y - _endPos.y );													// ‰Šú‚ÌŠp“x‚ð‚«‚ß‚é
		_radius = abs(_endPos.y - _startPos.y);															// ”¼Œa‚ÌÝ’è
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		_oneMoveVec = ((_endPos - _startPos) / 120.0);													// 2•bŒo‚Â‚Ü‚Å‚ÉˆÚ“®‚³‚¹‚é‚PÌÚ°Ñ‚ÌˆÚ“®—Ê
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
	// ÅI’n“_‚ÌêŠ‚©Áª¯¸
	if (abs(_endPos.x - _pos.x) >= abs(_oneMoveVec.x))
	{
		// ˆê”ÔÅ‰‚É‘OÌÚ°Ñ‚É‚¢‚½À•W‚ðŠi”[‚·‚é
		_oldPos = _pos;

		// ¼¸ÞÓ²ÄÞŠÖ”
		_pos.y = ((1.0 / (1.0 + exp(-_moveGain))) * (_endPos.y - _startPos.y)) + _startPos.y;

		// XˆÚ“®
		_pos.x += _oneMoveVec.x;

		// ¡‚ÌÀ•W‚Æ‘O‚ÌÀ•W‚ÅŠp“x‚ðŒvŽZ‚·‚é
		_lenght = _pos - _oldPos;
		_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90);

		// •‚ð•Ï‚¦‚é
		_moveGain += 0.1;
	}
	else
	{
		_pos = _endPos;																// ˆê‰ž‚¸‚ê‚ðC³‚·‚é
		SetMovePrg();
	}
}

void EnemyMove::MoveSpiral(void)
{

	// I—¹ðŒ
	if (_radius >= 0)
	{
		// ˆê”ÔÅ‰‚É‘OÌÚ°Ñ‚É‚¢‚½À•W‚ðŠi”[‚·‚é
		_oldPos = _pos;


		// ˆÚ“®
		_pos.x = (_radius * std::cos(_angle)) + _endPos.x;
		_pos.y = (_radius * std::sin(_angle)) + _endPos.y;

		// Šp“x§Œä
		_angle += std::atan(0.03) ;

		// ”¼Œa¬‚³‚­‚·‚é
		_radius -= 0.4;

		// ¡‚ÌÀ•W‚Æ‘O‚ÌÀ•W‚ÅŠp“x‚ðŒvŽZ‚·‚é
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
	
	if (abs(_endPos - _pos) >= abs(_oneMoveVec))								// X‚©Y‚¾‚¯‚ðÁª¯¸‚·‚é‚±‚Æ‚É‚æ‚Á‚ÄŒvŽZ—Ê‚ªŒ¸‚é
	{
		// ˆÚ“®—Ê‚ªŽc‚Á‚Ä‚¢‚éê‡
		_pos += _oneMoveVec;

		// Šp“x‚Ìˆ—
		_lenght = _endPos - _pos;													// Œ´“_‚É‡‚í‚¹‚é
		_rad = std::atan2(_lenght.y, _lenght.x) + (3.141592 * 90.0 )/ 180.0;		// Šp“x‚ð‘ª‚é
		//_rad = std::atan2(_lenght.y, _lenght.x) + std::atan(90.0);
		//_rad = std::atan2(-_pos.x + _endPos.x, -_endPos.y + _pos.y);
	}
	else
	{
		// Ši”[‚µI‚í‚Á‚½‚çØ‚è‘Ö‚¦‚é
		_pos = _endPos;																// ˆê‰ž‚¸‚ê‚ðC³‚·‚é
		_rad = 0;																	// “®‚«I‚í‚Á‚½‚çŠp“x‚ð‚à‚Æ‚ÌˆÊ’u‚É–ß‚·
		SetMovePrg();
	}
}

void EnemyMove::Wait(void)
{
	// I’[’n“_‚É—ˆ‚½‚çØ‚è‘Ö‚¦‚é
	if (count > _aim[_aimCnt].second.x)
	{
		SetMovePrg();
	}
	count++;
}

void EnemyMove::MoveLR(void)
{

}
