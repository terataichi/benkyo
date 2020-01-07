#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <Vector2.h>
#include "DIR.h"

#define PI 3.141592						// �~����
#define BLOCK_SIZE 16

enum class ANIMSTATE
{
	NORMAL,			// �ʏ�
	DETH,			// (���S)
	MAX
};

class Obj;			// �������߾ݹ�݂Ă���
using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;
using BlockMap = std::map < DIR, std::vector<std::vector<int>>>;

class Obj
{
public:
	Obj();
	virtual void Update() = 0;
	virtual void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const ANIMSTATE state);								// ��ҷ��̐ݒ�

	// �ق������̂�Ԃ�����
	const ANIMSTATE state(void) const;								
	const Vector2 &pos(void) const;
	const Vector2 &size(void) const;
	const BlockMap &blockData(void) const;
	const DIR &dir(void) const;

	// ���
	bool SetAnim(const ANIMSTATE state, AnimVector& data);			// ��Ұ���data�̓o�^
	virtual bool SetAlive(bool alive);
	bool SetState(ANIMSTATE state);
	bool SetBlock(BlockMap data);								// ��ۯ��̓��e������������Ƃ��Ɏg��
	bool isAlive(void) { return _alive; }						// ��Ԃ��擾���邽�߂���
	bool isDead(void) { return _dead; }
	bool isAnimEnd(void);										// ��Ұ��ݏC���m�F
protected:
	bool _moveFlg;												// ���삵�Ă����׸�

	bool DestroyPrpc(void);
	bool _alive;												// �����Ă��邩
	bool _dead;													// ����ł��邩
	Vector2 _pos;												// ���W
	Vector2 _size;												// �摜����
	Vector2 _upLeft;											// ڸĸ��̂̍���̍��W
	double _rad;												// �p�x
	int _zOder;													// �`��̗D��

	std::map<ANIMSTATE, AnimVector> _animMap;						// ��Ұ��݊i�[
	ANIMSTATE _state;												// ���
	unsigned int _animFrame;									// ��Ұ��ݗp�ڰ�
	unsigned int _animCount;									// ��Ұ��ݗp����
	BlockMap _blockData;	// ��ۯ����ް��i�[�p
	DIR _dir;													// ��ۯ��̌���
};

